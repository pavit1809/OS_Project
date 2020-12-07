var express=require("express");
var app=express();
var bodyparser=require("body-parser");

app.use(express.static("cssresources"));
app.use(bodyparser.urlencoded({extended:true}));
app.set("view engine","ejs");


// ====================>
// CONNECTING TO DB!!!
const mongoose=require("mongoose");
const { stringify } = require("querystring");
const { Console } = require("console");
mongoose.connect('mongodb://localhost/demo_db_OS', {
  useNewUrlParser: true,
  useUnifiedTopology: true
})
.then(() => console.log('Connected to DB!'))
.catch(error => console.log(error.message));

//CREATING A SCHEMA
var userschema=new mongoose.Schema({
   name: String,
   age: Number,
   Phone_no: String,
   Aadhaar_no: Number,
   Severity_cough: Number,
   Severity_fever: Number,
   Severity_breathlessness: Number,
   neurological_history: Number,
   cardiovascular_history: Number,
   gastric_history: Number,
   reference_number: Number,
   Booking_time: String
});
var User=mongoose.model("User",userschema);
// =================!
// ===============>
// ROUTES
app.get("/",function(request,response){
   var tt="";
   response.render("landing",{tt});
});
app.get("/developerinfo",function(request,response){
   response.render("developers");
});
app.get("/openform",function(request,response){
   var currtime=new Date().toLocaleTimeString();
   // console.log(currtime);  
   var currhr=parseInt(currtime[0]+currtime[1]);
   var currmin=currtime[2]+currtime[3];
   var currmerr=currtime[currtime.length-2]+currtime[currtime.length-1];
   currmin=parseInt(currmin);
   User.countDocuments({},function(err,counter){
      if (err){
         console.log(err);
      }
      else{
         if (counter<=19 && (currhr>=4 && currhr<=11 && currmerr=="PM")){
            response.render("form");
         }
         else{
            var tt="";
            if (counter>=20){
               tt="The Appointment queue is full!\nPlease try in some other centres or try again tommorow";
            }
            else if (currhr<=4 || currmerr=='AM'){
               tt="Booking starts at 4:00 PM";
            }
            else if (currhr>=10){
               tt="You are late!!! Booking ended at 7:00 PM.\nPlease try in some other centres or try again tommorow.";
            }
            response.render("landing",{tt});
         }
         
      }
   })
});
app.get("/contact",function(request,response){
   response.render("contact");
});
app.get("/check",function(request,response){
   response.render("check_status");
});
app.post("/appointment",function(request,response){
   // console.log(request.body);
   var degree_fever=0;
   var degree_cough=0;
   var degree_breathlessness=0;
   var iscardio=0;
   var isgastric=0;
   var isneuro=0;
   degree_fever=request.body.selected_degree_fever;
   degree_cough=request.body.selected_degree_cough;
   degree_breathlessness=request.body.selected_degree_breathlessness;
   let check_neuro=request.body['history_brain'];
   if (check_neuro!=undefined){
      isneuro=1;
   }
   let check_cardio=request.body['history_cardio'];
   if (check_cardio!=undefined){
      iscardio=1;
   }
   let check_gastric=request.body['history_gastric'];
   if (check_gastric!=undefined){
      isgastric=1;
   }
   var newuser={
      name: request.body.Patient_name,
      age: request.body.Patient_age,
      Phone_no: request.body.Patient_phone,
      Aadhaar_no:request.body.UID,
      Severity_cough: degree_cough,
      Severity_fever: degree_fever,
      Severity_breathlessness: degree_breathlessness,
      neurological_history: isneuro,
      cardiovascular_history: iscardio,
      gastric_history: isgastric,
      reference_number: Math.floor((Math.random() * 1000) + 1),
      Booking_time: new Date().toLocaleTimeString()
   };
   var tt="";
   var refno=newuser.reference_number;
   User.find({Phone_no:newuser.Aadhaar_no},function(err,samedata){
      if (err){
         console.log("You have already booked an appointment!!!");
      }
      else{
         if (samedata.length>=1){
            tt="You have already booked an appointment!!!";
            response.render("landing",{tt});
         }
         else{
            console.log(newuser);
            User.create(newuser,function(err,user){
               if (err){
                  tt="Sorry for the inconvenience caused.Please try again !!!"
               }
               else{
                  tt="Your appointment is Booked!!! \nPlease check your appointment under the FORM Menu.\nNOTE: The appointment time is subject to change. Please visit the site after 8:00 PM today to know your final appointment status.\nPlease keep in mind that the test takes 30 minutes, so plan your day accordingly.\nMask and gloves are MUST.\nYour reference number is "+refno;
                  response.render("landing",{tt});
               }
            })
         }
      }
   })
})
app.get("/finaloutput",function(request,response){
   var qq=parseInt(request.query.tellme);
   User.find({reference_number:qq},function(err,records){
      if (err){
         console.log(err);
      }
      else{
         if (records.length==0){
            var tt="Invalid Reference Id!.\n Please try again.";
            response.render("landing",{tt})
         }
         else{
            User.find({},function(err,allrecords){
               if (err){
                  console.log(err);
               }
               else{
                  console.log(allrecords);
                  response.render("check_status2",{data:allrecords,prefno:qq});
               }
            });
         }
      }
   });
});
app.listen(process.env.PORT || 3000,process.env.IP,function()
{
	console.log("Server started!!!");
});   