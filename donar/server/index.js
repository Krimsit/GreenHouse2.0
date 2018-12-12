// sudo chmod a+rw /dev/ttyACM0
// or
// sudo touch /dev/ttyACM0 && sudo chmod a+rw /dev/ttyACM0

var app = require('express')();
var http = require('http').Server(app);
var io = require("socket.io")(http);


var SerialPort = require('serialport');
var serialPort = new SerialPort("COM3", {
	baudRate: 9600,
});


serialPort.on("open", function () {
	console.log("open");
	io.on("connection", function(socket){
		console.log("connected!");
		socket.on("change", function(data){
			console.log(data.data);
			serialPort.write(data.data + "\n");
		});
		serialPort.on("data", function(data) {
			try{
				var val = JSON.parse(data.toString('utf8'));
				console.log(val)
				if (val == 0){
					socket.emit("click", {data: false});
				}
				else{
					socket.emit("click", {data: true});
				}
			}
			catch(err){
				// This error showed on console
			}
		}); 
	});
});


serialPort.on("error", function(err){
	console.log(err);
});
serialPort.on("close", function(){
	console.log("closed!");
});
serialPort.on("disconnect", function(){
	console.log("disconnected!");
});


app.get('/', function(req, res){
  res.send('<a href="http://192.168.100.1:9000">На Клиент!</a>');
});

http.listen(3000, function(){
  console.log('listening on *:3000');
});
