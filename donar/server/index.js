// sudo chmod a+rw /dev/ttyACM0
// or
// sudo touch /dev/ttyACM0 && sudo chmod a+rw /dev/ttyACM0

var app = require('express')();
var http = require('http').Server(app);
var io = require("socket.io")(http);


var SerialPort = require('serialport');
var serialPort = new SerialPort("COM5", {
	baudRate: 250000,
});

var _MAIN_DATA = [];

serialPort.on("open", function(){
	io.on("connection", function(socket){
		var i = 0;
		serialPort.on("data", function(data){
			try{
				socket.emit("tmp", {data: JSON.parse(data.toString('utf8'))});	
			}
			catch(err){
				// Err
			}
		})
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
  res.send('<a href="http://192.168.0.1:3000">На Клиент!</a>');
});

http.listen(9000, function(){
  console.log('listening on *:9000');
});

/*
	1. Сбор данных
		а. Каждую минуту компануется пакет из 4 (основа), 
	2. Панель упарвления
		а. 

*/
