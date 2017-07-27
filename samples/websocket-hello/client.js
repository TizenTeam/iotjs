//#!/usr/bin/env node

var console = require('console');
var WebSocket = require('websocket').w3cwebsocket;
var url= "ws://localhost:1337/";
var ws = new WebSocket(url);
//var timers = require('timers');

function log(message)
{
    var text;
    try {
        text = JSON.stringify(message);
    } catch(err) {
        text = message;
    };
    console.log("log: client.js: " + text);
}

function main(connection)
{
    log("{ main");
    log(url);
    ws.onopen = function() {
        log("onopen: {")
        ws.send("hello Websocket!");
        log("onopen: }")
    }
    ws.onclose = function() {
        log("onclose:");
    }

    /// https://developer.mozilla.org/en-US/docs/Web/API/MessageEvent
    ws.onmessage = function(evt){
        log("onmessage");
        log(evt.data);
    };
    //ws.close(ws);


    log("} main");
}

main();


// TODO:
// NODE_MODULES=../node_modules/websockets/ node samples/websocket-hello/server.js 
