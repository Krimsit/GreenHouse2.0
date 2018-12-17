// sudo chmod a+rw /dev/ttyACM0
// or
// sudo touch /dev/ttyACM0 && sudo chmod a+rw /dev/ttyACM0

var app = require('express')();
var http = require('http').Server(app);
var io = require("socket.io")(http);
var fs = require("fs");

const path_NORMS = "./NORMS.json"

// var NORMS = fs.readFile("./NORMS.json", "utf-8", (err, data) => {
// 	if(err) console.log(err);
// 	return JSON.parse(data).NORMS;
// });

var NORMS = JSON.parse(fs.readFileSync(path_NORMS, "utf-8")).NORMS;
var AutoMode = false;
var light = false;
/*
	{
	"NORMS": {
		"Idr": 30,
		"Temp": 26,
		"HumAir": 60,
		"HumSoil": 80
	}
}
*/
var changeNORMS = data => {
	NORMS[Object.keys(data)[0]] = data[Object.keys(data)[0]];
	// console.log(NORMS);
	let _str = JSON.stringify({NORMS: NORMS});
	// console.log(_str);
	console.log("Change Data");
	fs.writeFileSync(path_NORMS, _str, err => {
		if(err) console.log("Проблемы с записью информации в файл");
	})
};


var SerialPort = require('serialport');
var serialPort = new SerialPort("COM5", {
	baudRate: 250000,
});

var _mode_sensors = 0;

serialPort.on("open", function(){
	io.on("connection", function(socket){
		socket.emit("INIT", {type: "NORMS", payload: NORMS});
		var i = 0;
		serialPort.on("data", function(data){
			try{
				// console.log(JSON.parse(data.toString('utf8')));
				switch(_mode_sensors){
					case 0:{
						let value = JSON.parse(data.toString('utf8'));
						console.log(AutoMode, value, NORMS.Idr, (NORMS.Idr - value) / NORMS.Idr, !light);
						if (AutoMode && value < NORMS.Idr && ((NORMS.Idr - value) / NORMS.Idr  > 0.1) && !light){
							serialPort.write(128 + "\n");
						}
						else{
							serialPort.write(256 + "\n");
						}
						
						socket.emit("GET_DATA", {type: "Idr", payload: value});
					}break;
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
					serialPort.write(ans + "\n");break;
			}
		})

		socket.on("control", data => {
			switch(data.type){
				case "light": {
					_mode_control = 0;
					let bin_int = [
						0,0,0,0,0,0,0
					];
					bin_int[4] = 1;
					let _str = bin_int.join('');
					let ans = parseInt(_str, 2);
					serialPort.write(ans + "\n");
				};break
				case "temp": {
					_mode_control = 1;
					let bin_int = [
						0,0,0,0,0,0,0
					];
					bin_int[5] = 1;
					let _str = bin_int.join('');
					let ans = parseInt(_str, 2);
					serialPort.write(ans + "\n");
				};break;
				case "pomp": {
					_mode_control = 2;
					let bin_int = [
						0,0,0,0,0,0,0
					];
					bin_int[6] = 1;
					let _str = bin_int.join('');
					let ans = parseInt(_str, 2);
					serialPort.write(ans + "\n");
				};break
			}
		})
		socket.on('changeNORMS', (data) => {
			changeNORMS({ Idr: data.Idr })
			changeNORMS({ Temp: data.Temp })
			changeNORMS({ HumSoil: data.HumSoil })
			changeNORMS({ HumAir: data.HumAir })
		});
		socket.on("autoMode", data => {
			AutoMode = data.payload;
		});
	});
	io.on("disconnect", socket => {
		console.log("Disconnect");
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
  console.log(NORMS);
});
