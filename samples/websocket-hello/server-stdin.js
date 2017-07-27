#!/usr/bin/env node

var webSocketsServerPort = 1337;
var delay = 3000;

var fs = require('fs');
var WebSocketServer = require('websocket').server;
var http = require('http');

var server = http.createServer(function(request, response) {
    // process HTTP request. Since we're writing just WebSockets server
    // we don't have to implement anything.
});

function log(message)
{
    var text = JSON.stringify(message)
    console.log("log: " + text);
}

server.listen( webSocketsServerPort , function() {
    log((new Date()) + " Server is listening on port " + webSocketsServerPort);
});

/** create the server : https://www.npmjs.com/package/nodejs-websocket **/
wsServer = new WebSocketServer({
    httpServer: server
});


function sendEvent(connection, text)
{
    log("sendEvent");
    if (null == text) {
        text = "" + new Date();
    }
    connection.send(text);
    log(text);
}


function start(connection)
{
    log("start");
    // var id = setInterval( function() { sendEvent(connection); } , delay);
    //TODO: clearInterval(id);
    process.stdin.resume();
    process.stdin.setEncoding('utf8');
    process.stdin.on('data', function(data) {
        log(data);
        sendEvent(connection, data);
    });

}

log(process.argv)

// WebSocket server
wsServer.on('request', function(request) {
    var connection = request.accept(null, request.origin);
    log("on: request");
    // This is the most important callback for us, we'll handle
    // all messages from users here.

    connection.on('message', function(message) {
        log("on: message");
        start(connection);
        log(message);
        if (message.type === 'utf8') {
            // process WebSocket message
            log(message.utf8data);
        }
    });

    connection.on('close', function(connection) {
        log("on: close");
        // close user connection
    });
});

log("finishing");
//# philippe@wsf1127:iotjs/ # [130] # while true ; do date -u +"%s" ; sleep ${delay} ; done  |  NODE_MODULES=.. nodejs  samples/websocket-hello/server-stdin.js 


