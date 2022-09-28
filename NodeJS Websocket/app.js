const WebSocket = require("ws").Server;
const { createServer } = require("https");
const fs = require("fs");

const server = createServer({
  cert: fs.readFileSync("certificate.crt"),
  key: fs.readFileSync("privateKey.key"),
},function (req, res) {
    res.writeHead(200);
    res.end("hello world\n");
  });
const socket = new WebSocket({
  server,
});

counter=0

console.log("YEP")
socket.on('connection',socket => {
    console.log("connection detected")
    socket.on('message',message=>{
        console.log("From Server:",message+"")
        socket.send('IM SENDING THIS BACK THERE, ROGERB: '+message+" "+ counter)
        counter+=1
    })
});

// socket.on('data',socket => {
//     console.log("DATA SENT",data)
//     socket.on('message',message=>{
//         console.log("From Server:",message+"")
//         socket.send('IM SENDING THIS BACK THERE, ROGERA:'+message)
//     })
// });
portNum=4334
console.log("listening on ",portNum)
server.listen(portNum);