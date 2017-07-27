//#!/usr/bin/env node

var console = require('console');
var WebSocket = require('websocket').w3cwebsocket;
var url= "ws://localhost:1337/";
var ws = new WebSocket(url);

function log(message)
{
    var text = JSON.stringify(message)
    console.log("log: client.js: " + text);
}

function idle_(num)
{
    for(var i=0; i<num; i++) {
        log("idle:" + i);
        ws.idle_() 
    }
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

    idle_(0x8); 
    ws.close(ws);
    idle_(0x8);
    log("} main");

}

main();
