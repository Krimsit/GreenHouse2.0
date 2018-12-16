// sudo chmod a+rw /dev/ttyACM0
// or
// sudo touch /dev/ttyACM0 && sudo chmod a+rw /dev/ttyACM0

var app = require('express')();
var http = require('http').Server(app);
var io = require("socket.io")(http);


var SerialPort = require('serialport');
var serialPort = new SerialPort("COM3", {
	baudRate: 250000,
});

var _mode_sensors = 0;

serialPort.on("open", function(){
	io.on("connection", function(socket){
		var i = 0;
		serialPort.on("data", function(data){
			try{
				console.log(JSON.parse(data.toString('utf8')));
				switch(_mode_sensors){
					case 0:
						socket.emit("GET_DATA", {type: "Idr", payload: JSON.parse(data.toString('utf8'))});break;
					case 1:
						socket.emit("GET_DATA", {type: "Temp", payload: JSON.parse(data.toString('utf8'))});break;
				}
				
			}
			catch(err){
				// Err
			}
		})
		socket.on("change_get_data", data => {
			/*
				10000000
			*/
			
			switch(data.type){
				case "Idr":{
					_mode_sensors = 0;
					let bin_int = [
						0,0,0,0,0,0,0
					];
					bin_int[0] = 1;
					let _str = bin_int.join('');
					let ans = parseInt(_str, 2);
					console.log(bin_int, _str, ans);
					serialPort.write(ans + "\n");
				}break;
				case "Temp":
					_mode_sensors = 1;
					let bin_int = [
						0,0,0,0,0,0,0
					];
					bin_int[1] = 1;
					let _str = bin_int.join('');
					let ans = parseInt(_str, 2);
					console.log(bin_int, _str, ans);
					serialPort.write(ans + "\n");break;
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