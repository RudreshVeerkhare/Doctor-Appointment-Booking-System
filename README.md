
# Doctor-Appointment-Booking-System  
This is my First year project based on MySQL C API, GTK,libcurl and espeak.  
This application will only run on linux based operating system.  
  
  
# Steps to run program :  
1)Open terminal in project folder.  
2)Use command `sudo su` to run terminal into superuser mode  
3)Use command `make install` to install all prerequisites for program.  
4)Finally use command `make` to run program.  
  
# Instructions :  
This application consists of two interfaces : 1)admin 2)User  
       **admin interface :**   
        username : admin password : admin1234  
        it's for keeping record of available doctors.  
        **Adding doctor :**  
          Doctor can be added by entering doctor name ,doctor's starting time and ending time.  
          Time should be in 24 hrs format and can be only integral hours  
              ex. 1200,1500,2300..  
        **Removing Doctor :**   
          Doctor can be removed by selecting and then pressing remove button.  
    **User interface :**  
        you have to create an account through sign up option **Please enter valid email as a mail will be sent**.  
        Once you created an account then you can login using your gmail and password.  
        **Booking Appointment :**  
            To book an appointment you have to enter time for appointment **Entered time must be in format specified in admin interface**  
            A mail will be sent to your given email contaning information of your appointment.  
            In myprofile section there will be a button for simple chatbot Alex based on direct string comparison, you can check for list of supported input in *gchat.txt* file.  
        
**Thanks for visiting...  
Suggetions are welcome....**
