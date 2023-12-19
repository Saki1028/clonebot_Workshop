static const char PROGMEM INDEX_HTML[] = R"rawliteral(
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body { font-family: Arial, Helvetica, sans-serif; text-align: center; margin:10px auto; padding-top: 30px;}
      table { margin-left: auto; margin-right: auto; text-align: center;}
      td { padding: 1px; text-align: center; margin: 2px 1px;}
      .button {
        border: none;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        font-weight: bold;
        margin: 2px 1px;
        cursor: pointer;
        -webkit-touch-callout: none;
        -webkit-user-select: none;
        -khtml-user-select: none;
        -moz-user-select: none;
        -ms-user-select: none;
        user-select: none;
        -webkit-tap-highlight-color: #b3c8d6ff;
        border-radius: 8px;
        height: 100%;
        width: 85px;
        border: 2px  solid;
        border-color: rgba(255, 255, 255, 0);
      }
      .button1 {
        background-color: #73a4c1ff;
        color: #375d81ff;
      }
      .button2 {
        background-color: #b3c8d6ff;
        color: #e1e6faff;
      }
      .button3 {
        background-color: #f6dddfff;
        color: #df9c9dff;
      }
      .button4 {
        background-color: #d1e1e9ff;
        color: #5a8dabff;
      }
      .button5 {
        background-color: #b0d1d1ff;
        color: #5a8dabff;
      }
      .button:hover {opacity: 0.8;}
      .button:active {
        transform: scale(0.98);
        /*box-shadow: 3px 2px 1px 1px #b3c8d6ff;*/
        border: 2px solid;
        border-color: #b3c8d6ff;
      }
      img {  max-width: 100% ;
      }
      kbd {
        background-color: #eee;
        border-radius: 3px;
        border: 1px solid #b4b4b4;
        box-shadow: 0 1px 1px rgba(0, 0, 0, .2), 0 2px 0 0 rgba(255, 255, 255, .7) inset;
        color: #333;
        display: inline-block;
        font-size: .85em;
        font-weight: 700;
        line-height: 1;
        padding: 2px 4px;
        white-space: nowrap;
      }
    </style>
  </head>
  <body>
    <img src="" id="photo" width="300px";>
    <table>
      <tr><td colspan="5" align="center"><button class="button button1" onmousedown="toggleCheckbox('ffront');" ontouchstart="toggleCheckbox('ffront');">&#8607</button></td></tr>
      <tr><td colspan="5" align="center"><button class="button button1" onmousedown="toggleCheckbox('front');" ontouchstart="toggleCheckbox('front');">&#9650</button></td></tr>
      <tr><td align="center"><button class="button button1" onmousedown="toggleCheckbox('left');" ontouchstart="toggleCheckbox('left');">&#9668</button></td><td align="center"></td><td align="center"><button class="button button4" onmousedown="toggleCheckbox('stop');" ontouchstart="toggleCheckbox('stop');">&#9724</button></td><td align="center"></td><td align="center"><button class="button button1" onmousedown="toggleCheckbox('right');" ontouchstart="toggleCheckbox('right');">&#9658</button></td></tr>
      <tr><td colspan="5" align="center"><button class="button button1" onmousedown="toggleCheckbox('back');" ontouchstart="toggleCheckbox('back');">&#9660</button></td></tr>
      <tr><td colspan="5" align="center"><button class="button button1" onmousedown="toggleCheckbox('fback');" ontouchstart="toggleCheckbox('fback');">&#8609</button></td></tr>                 
    </table>
    <table>
      <tr><td align="center"><button class="button button3" onmousedown="toggleCheckbox('lift');" ontouchstart="toggleCheckbox('lift');">&#10595</button></td><td align="center"></td><td align="center"><button class="button button2" onmousedown="toggleCheckbox('down');" ontouchstart="toggleCheckbox('down');">&#10597</button></td></tr>
      <tr><td align="center"><button class="button button3" onmousedown="toggleCheckbox('on');" ontouchstart="toggleCheckbox('on');">&#127765</button></td><td align="center"></td><td align="center"><button class="button button2" onmousedown="toggleCheckbox('off');" ontouchstart="toggleCheckbox('off');">&#127761</button></td></tr>
      <tr><td colspan="3" align="center"><button class="button button1" onmousedown="toggleCheckbox('dance');" ontouchstart="toggleCheckbox('dance');">&#128131</button></td></tr>
    </table>
   <script>
    //<img src="" id="photo" width="250px" style="transform:rotate(-90deg);">
    
    function toggleCheckbox(x) {
     var xhr = new XMLHttpRequest();
     xhr.open("GET", "/action?go=" + x, true);
     xhr.send();
     }
    window.onload = document.getElementById("photo").src = window.location.href.slice(0, -1) + ":81/stream";
        
    let gp;
    let axisYaw;
    let axisDi;
    let gpconnected = 0;
    let cmd;
    let cmd2;
    let joystick = 'm';
    let rightWheel = 0;
    let leftWheel = 0;
    var loopy;
    //let loopy = setInterval(gpUpdated, 100);

    var gamepadConnected = function () {
      gp = navigator.getGamepads();
      console.log(gp[0]);
      console.log("Connected!");
      gpconnected = 1;
      loopy = setInterval(gpUpdated, 200);
      };
    var gamepadDisconnected = function () {
      console.log("Disconnected!");
      gpconnected = 0;
      clearInterval(loopy);
      };
    
    function map(x, in_min, in_max, out_min, out_max) {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
      }

    var gpUpdated = function (){
      gp = navigator.getGamepads();
      axisYaw = (gp[0].axes[0] * 100).toFixed(0);
      axisDi = (gp[0].axes[1] * 100).toFixed(0);
      axisDi = map(axisDi, -100, 100, 100, -100);
      //console.log(axisYaw);
      //console.log(axisDi);
      if(axisYaw < -30 || axisYaw > 30 || axisDi < -30 || axisDi > 30){
        //console.log("#"+axisYaw+"@"+axisDi);
        cmd = 'joystick'; 
        if(axisDi < -30 || axisDi > 30){
          if (axisYaw > 20 || axisYaw < -20){
            rightWheel = (axisDi - (axisYaw/2*1));
            leftWheel = (axisDi + (axisYaw/2*1));
            }
          else{
            rightWheel = (axisDi*1);
            leftWheel = (axisDi*1);
            }
          }
        else if (axisYaw > 30 || axisYaw < -30){
          rightWheel = (axisYaw/2 * (-1));
          leftWheel = (axisYaw/2 * 1);
          }
        //console.log("#"+rightWheel+"@"+leftWheel);
        if (rightWheel >= 0){
          rightWheel = (map(rightWheel, 10, 135, 1024, 2047) + 1000).toFixed(0);
        }
        else{
          rightWheel = (map(rightWheel, -10, -135, 0, 1023) + 1000).toFixed(0);
        }

        if (leftWheel >= 0){
          leftWheel = (map(leftWheel, 10, 135, 0, 1023) + 1000).toFixed(0);
        }
        else{
          leftWheel = (map(leftWheel, -10, -135, 1024, 2047) + 1000).toFixed(0);
        }
        //console.log(joystick);
        joystick = 'm' + rightWheel + 'm' + leftWheel;
        toggleCheckbox(joystick);
        console.log(joystick);
        }
      else if (gp[0].buttons[14].pressed){
        if (cmd != 'left'){
          cmd = 'left'; 
          toggleCheckbox('left');
          console.log("left");
          }
        }
      else if (gp[0].buttons[15].pressed){
        if (cmd != 'right'){
          cmd = 'right'; 
          toggleCheckbox('right');
          console.log("right");
          }
        }
      else if (gp[0].buttons[12].pressed){
        if (cmd != 'front'){
          cmd = 'front'; 
          toggleCheckbox('front');
          console.log("front");
          }
        }
      else if (gp[0].buttons[13].pressed){
        if (cmd != 'back'){
          cmd = 'back'; 
          toggleCheckbox('back');
          console.log("back");
          }
        }
      else if (gp[0].buttons[3].pressed){
        if (cmd != 'ffront'){
          cmd = 'ffront'; 
          toggleCheckbox('ffront');
          console.log("ffront");
          }
        }
      else if (gp[0].buttons[0].pressed){
        if (cmd != 'fback'){
          cmd = 'fback'; 
          toggleCheckbox('fback');
          console.log("fback");
          }
        }
      else{
        if (cmd != 'stop'){
          cmd = 'stop'; 
          toggleCheckbox('stop');
          console.log("stop");
          }
      }

      if (gp[0].buttons[7].pressed){
        if (cmd2 != 'lift'){
          cmd2 = 'lift'; 
          toggleCheckbox('lift');
          console.log("lift");
          }
        }
      else if (gp[0].buttons[6].pressed){
        if (cmd2 != 'down'){
          cmd2 = 'down'; 
          toggleCheckbox('down');
          console.log("down");
          }
        }
      else if (gp[0].buttons[5].pressed){
        if (cmd2 != 'on'){
          cmd2 = 'on'; 
          toggleCheckbox('on');
          console.log("on");
          }
        }
      else if (gp[0].buttons[4].pressed){
        if (cmd2 != 'off'){
          cmd2 = 'off'; 
          toggleCheckbox('off');
          console.log("off");
          }
        }
    }

   window.addEventListener('gamepadconnected', gamepadConnected);
   window.addEventListener('gamepaddisconnected', gamepadDisconnected);

   document.addEventListener("keydown", function(event) {
    event.preventDefault();
    if (event.keyCode == 37) {
      toggleCheckbox('left');
    }
    else if(event.keyCode == 39) {
      toggleCheckbox('right');
    }
    else if(event.keyCode == 38) {
      toggleCheckbox('front');
    }
    else if(event.keyCode == 40) {
      toggleCheckbox('back');
    }
    else if(event.keyCode == 32 || event.keyCode == 13) {
      toggleCheckbox('stop');
    }
    else if(event.keyCode == 87) {
      toggleCheckbox('ffront');
    }
    else if(event.keyCode == 83) {
      toggleCheckbox('fback');
    }
    else if(event.keyCode == 76) {
      toggleCheckbox('lift');
    }
    else if(event.keyCode == 68) {
      toggleCheckbox('down');
    }
    else if(event.keyCode == 79) {
      toggleCheckbox('on');
    }
    else if(event.keyCode == 70) {
      toggleCheckbox('off');
    }
    else if(event.keyCode == 71) {
      toggleCheckbox('dance');
    }
   });
   </script>
  </body>
</html>
)rawliteral";
