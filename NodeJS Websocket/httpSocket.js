const WebSocket = require("ws").Server;
const { createServer } = require("http");
const fs = require("fs");


let counter=0;
let arr10000=[];
let arr1000=[];
let arr100=[];
let arr10=[];

let avg10=0
let avg100=0
let avg1000=0
let avg10000=0


function addToArr(targetArr,msg,size) {
    if (targetArr.length>=size){
        targetArr.shift()
    }
    targetArr.push(parseInt(msg))
  }

  function getAvg(tarArr){
    let sum=getSum(tarArr)
    //console.log("avg ",sum/tarArr.length)
    return sum/tarArr.length
  }

  function getSum(tarArr){
    //console.log("tarArr ",tarArr)
    let sum=0
    for (i=0;i<tarArr.length;i++){
        sum+=tarArr[i]
    }
    //console.log("sum ",sum)
    return sum
  }

const server = createServer({},function (req, res) {

    res.writeHead(200);
    res.end("AVERAGE 10    -  "+avg10.toString()+"\n"
    +"AVERAGE 100   -  "+avg100.toString()+"\n"
    +"AVERAGE 1000  -  "+avg1000.toString()+"\n"
    +"AVERAGE 10000 -  "+avg10000.toString());
  });
const socket = new WebSocket({
  server,
});



socket.on('connection',socket => {
    console.log("connection detected")
    socket.on('message',message=>{
        console.log("From Server:",message+"  "+counter)
        // server.end(message);
        // socket.send('IM SENDING THIS BACK THERE, ROGERB: '+message+" "+ counter)
        //console.log("PARSING",parseInt(message))
        if (!isNaN(parseInt(message))){
            addToArr(arr10,message,10)
            addToArr(arr100,message,100)
            addToArr(arr1000,message,1000)
            addToArr(arr10000,message,10000)

            avg10=getAvg(arr10)
            avg100=getAvg(arr100)
            avg1000=getAvg(arr1000)
            avg10000=getAvg(arr10000)

        }
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