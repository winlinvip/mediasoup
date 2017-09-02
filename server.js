#!/usr/bin/env node

'use strict';

console.log('WEBRTC SFU MediaSoup');

const mediasoup = require('./lib/mediasoup');
const http = require('http')

var mediaServer = mediasoup.Server({
    numWorkers       : 1,
    logLevel         : "debug",
    rtcIPv4          : true,
    rtcIPv6          : false,
    rtcAnnouncedIPv4 : null,
    rtcAnnouncedIPv6 : null,
    rtcMinPort       : 50000,
    rtcMaxPort       : 60000
});

var httpServer = http.createServer();
// https://nodejs.org/api/http.html#http_event_request
httpServer.on('request', function(request, response){
    response.write('Hello SFU!');
    response.end();
});
httpServer.listen(8080, '0.0.0.0');
