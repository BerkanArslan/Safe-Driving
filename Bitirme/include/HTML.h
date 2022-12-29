const char INDEX_HTML[] =
"<!DOCTYPE html>"
"<html>"
"<head>"
"<style>"
    
"	*, "
"*:before,"
"*:after {"
"  padding: 0;"
"  margin: 0;"
" box-sizing: border-box;"
"}"
"body {"
"background-color: rgba(118, 162, 197, 0.6);"
" background-size: cover;"
"background-repeat: no-repeat;"
  
"}"
"form {"
"height: 480px;"
" width: 400px;"
" background-color: rgba(0, 0, 0, 0.5);"
"position: absolute;"
" transform: translate(-50%, -50%);"
" top: 50%;"
" left: 50%;"
" border-radius: 10px;"
" backdrop-filter: blur(15px);"
"  border: 2px solid rgba(255, 255, 255, 0.1);"
" box-shadow: 0 0 40px rgba(8, 7, 16, 0.6);"
"  padding: 50px 35px;"
"}"
"form * {"
"font-family: \"Poppins\", sans-serif;"
"color: #ffffff;"
"letter-spacing: 0.5px;"
" outline: none;"
" border: none;"
"}"
"form h3 {"
"font-size: 40px;"
"font-weight: 700;"
" line-height: 42px;"
" text-align: center;"
"}"

"label {"
"display: block;"
"margin-top: 30px;"
"font-size: 16px;"
"font-weight: 500;"
"}"
"input {"
"display: block;"
"height: 50px;"
"width: 100%;"
"background-color: rgba(255, 255, 255, 0.05);"
"border-radius: 3px;"
" padding: 0 10px;"
"margin-top: 8px;"
" font-size: 14px;"
"font-weight: 300;"
"}"
"::placeholder {"
" color: #e1e1e1;"
"}"

"input:hover{"
"outline: 2px solid #0001;"
"}"
"button {"
"margin-top: 50px;"
"width: 100%;"
"background-color: #ffffff;"
"color: #080710;"
"padding: 15px 0;"
"font-size: 18px;"
"font-weight: 600;"
"border-radius: 5px;"
"cursor: pointer;"
"}"

"@media only screen and (max-width: 600px) {"
"body {"
"background-color : rgba(215, 221, 84, 0.7);"
"}"
"}"


" </style>"
"</head>"
"<body>"
  "<form>"
    "<h3>Connect Wifi</h3>"
    "<form action=\"/\" method=\"post\">"
    "<p>"
    "<label>SSID:&nbsp;</label>"
    "<input maxlength=\"30\" name=\"ssid\"><br>"
    "<label>Key:&nbsp;&nbsp;&nbsp;&nbsp;</label><input maxlength=\"30\" name=\"password\"><br>"
    "<button>Log In</button>"
    "</p>"
    "</form>"
    "</body>"

    "</html>";