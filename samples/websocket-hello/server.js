#!/usr/bin/env node
//# npm install websocket 

var webSocketsServerPort = 1337;
var delay = 3000;
var file = "/etc/os-release";

var fs = require('fs');
var http = require('http');

// https://www.npmjs.com/package/websocket
// https://www.npmjs.com/package/nodejs-websocket
var WebSocketServer = require('websocket').server;
var ReadableStream = Object.getPrototypeOf(process.stdin);

var server = http.createServer(function(request, response) {
    // process HTTP request. Since we're writing just WebSockets server
    // we don't have to implement anything.
});


function log(message)
{
    var text = JSON.stringify(message)
    console.log("log: " + text);
}


function sendEvent(connection, text)
{
    log("sendEvent");
    if (null == text) {
        text = "" + new Date();
    }
    connection.send(text);
    log(text);
}



server.listen( webSocketsServerPort , function() {
    log((new Date()) + " Server is listening on port " + webSocketsServerPort);
});

/** create the server : https://www.npmjs.com/package/nodejs-websocket **/
wsServer = new WebSocketServer({
    httpServer: server
});


log(process.argv)

// WebSocket server
wsServer.on('request', function(request) {
    log("on: request: ");
    var connection = request.accept(null, request.origin);
    log("on: request");
    
    if ( !true ) {
        var delay = 3000;
        var id = setInterval( function() { sendEvent(connection); } , delay);
    }

    // This is the most important callback for us, we'll handle
    // all messages from users here.

    connection.on('message', function(message) {
        log("on: message:");
        log(message);
        if (message.type === 'utf8') {
            // process WebSocket message
            log(message.utf8Data);
        }
    });

    connection.on('close', function(connection) {
        log("on: close: @server.js");
    });
});

log("finishing");
