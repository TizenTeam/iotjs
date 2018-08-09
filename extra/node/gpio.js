// -*- mode: js; js-indent-level:2;  -*-
// SPDX-License-Identifier: MPL-2.0
/**
 *
 * Copyright 2018-present Samsung Electronics France SAS, and other contributors
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.*
 */

function Gpio()
{
  this.DIRECTION = { "IN": "in", "OUT": "out" };
  
  this.open  = function(config, callback){
    callback(null);
    return this;
  }
  this.readSync = function(err) {
    return true;
  }
  this.closeSync = function() {
    return;
  }
  this.write = function(value) {
    return;
  }
  
}

  
module.exports = new Gpio();
