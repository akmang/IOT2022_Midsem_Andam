char page[] PROGMEM = R"(
<!DOCTYPE html>
<html>

<head>
    <title>Local network</title>
    <style>
        body {
            margin-top: 50px;
            font-family: Georgia
        }

        body {
            font-size: 20px;
            text-align: center
        }

        .btn {
            display: block;
            width: 200px;
            margin: auto;
            padding: 20px
        }

        .btn {
            font-size: 10px;
            color: black;
            text-decoration: none
        }

        .on {
            background-color: lightgreen
        }

        .off {
            background-color: lightskyblue
        }

        .zero {
            background-color: Thistle
        }

        td {
            font-size: 20px;
            margin-top: 50px;
            margin-bottom: 5px
        }

        p {
            font-size: 20px;
            margin-top: 50px;
            margin-bottom: 5px
        }
    </style>
</head>

<body>
    <h1>Dashboard</h1>
    <div>
    <p> Current Reading is </p> <p id="CurrentReading"></p>
</div>
    <table style='width:100%'>
        <tr>
            <td style="font-size:15px">Manual Operation</td>
            <td style="font-size:15px">Automatic Operation</td>
        </tr>
    </table>

    <table style='width:100%'>
        <tr>
            <td><button class='btn off' id='Manual' onclick='sendData(id)'>ON
                </button></td>
            <td><button class='btn off' id='Automatic' onclick='sendData(id)'>OFF
                </button></td>

        </tr>
        <tr>
            <td>
                <button pill class='btn off' id='Start' style="font-size:20px;width:100px;" onclick='sendData(id)'>
                    Start
                </button>
            </td>
        </tr>
        <tr>
            <td>
                <button pill class='btn off' id='Stop' style="font-size:20px;width:100px;" onclick='sendData(id)'>
                    Stop
                </button>
            </td>
        </tr>
    </table>
    </table>

    <!-- Auto off, Man off - 0 -->
    <!-- Auto on, Man off -  1 -->
    <!-- Auto off, Man on -  2 -->
    <!-- Auto on, Man on -   ! -->
    <div hidden id="send_enabled">0</div>


    <script>
        function set_mode_signal(code) {
            document.getElementById("send_enabled").innerText = code
        }

        function get_mode_signal(code) {
            return document.getElementById("send_enabled").innerText;
        }




        function set_manual_controls(is_enabled) {
            let start_btn = document.getElementById("Start");
            let stop_btn = document.getElementById("Stop");

            let man_start = document.getElementById("Start")
            let man_stop = document.getElementById("Stop")

            if (is_enabled) {
                start_btn.removeAttribute("disabled")
                stop_btn.removeAttribute("disabled")
            } else {
                start_btn.setAttribute("disabled", true)
                stop_btn.setAttribute("disabled", true)
                man_start.className = "btn off"
                man_stop.className = "btn off"

            }
        }



        function update_Op_Btn(self_cls, other_cls) {

            let self = document.getElementById(self_cls);
            let other = document.getElementById(other_cls);

            let old_state = self.className;

            self.className = old_state == 'btn on' ? 'btn off' : 'btn on';
            self.innerHTML = old_state == 'btn on' ? 'OFF' : 'ON';
            other.className = old_state == 'btn off' ? 'btn off' : other.className;
            other.innerHTML = old_state == 'btn off' ? ' OFF' : other.innerHTML;

        }


        function send_state_to_arduino() {
            let state = get_send_signal();
        }

        function sendData(butn) {
            var URL, text;
            if (butn == 'Manual') {
                URL = '/status/0';
                variab = '0';
            } else if (butn == 'Automatic') {
                URL = '/status/1';
                variab = '1';
            } else if (butn == 'Start') {
                if (butn == 'Manual') {
                    URL = '/status/0';
                    variab = '0';
                } else {
                    URL = '/status/2';
                    variab = '2';
                }
            } else if (butn == 'Stop') {
                URL = '/status/0';
                variab = '0';
            } 

            // change button class and text 
            if (butn == 'Manual') {
                update_Op_Btn('Manual', 'Automatic')
                set_manual_controls(true);
                set_mode_signal(0);
            }

            if (butn == 'Automatic') {
                update_Op_Btn("Automatic", "Manual")
                set_manual_controls(false);
                set_mode_signal(1);
            }


            if (butn == 'Stop') {

                let self = document.getElementById("Stop");
                let other = document.getElementById("Start");

                let old_state = self.className;

                self.className = old_state == 'btn on' ? 'btn off' : 'btn on';
                other.className = old_state == 'btn off' ? 'btn off' : other.className;

                set_mode_signal(0);

            }
            if (butn == 'Start') {
                let self = document.getElementById("Start");
                let other = document.getElementById("Stop");

                let old_state = self.className;

                self.className = old_state == 'btn on' ? 'btn off' : 'btn on';
                other.className = old_state == 'btn off' ? 'btn off' : other.className;

                set_mode_signal(2);
            }


            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function (butn) {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById(variab).innerHTML = this.
                        responseText;
                }
            };
            xhr.open('GET', URL, true);
            xhr.send();
        }

        setInterval(reload, 1000);
        function reload() {
            var xhr = new XMLHttpRequest();
            xhr.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200)
                    document.getElementById('CurrentReading').innerHTML = this.
                        responseText;
            };
            xhr.open('GET', '/CurrentReading', true);
            xhr.send();
        }


    </script>
    </section>
</body>

</html>

</html>
)";
