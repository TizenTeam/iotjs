var https = require("https");
//var net = require('net');
var url =
  'https://api.openweathermap.org/data/2.5/weather?q=London,uk%20forecast?id=524901&APPID=c96d8df876bd744bed69e40c4fc891f7';
https.get(url, function(res) {
  res.setEncoding("utf8");
  var body = "";
  res.on("data", function(data) {
    body += data;
  });
  res.on("end", function() {
    body = JSON.parse(body);
    console.log(body);
    console.log(body.visibility);
    if (body.visibility < 10001)
    {
      console.log("turn light on");
  //    socket.end('Hello IoT.js');
    }
  });
});
