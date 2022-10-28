<!DOCTYPE html>
<html>
<body>
<h1>Dashboard</h1>
    <table> 
        <div id="WaterLevel"></div>
    </table>


    <script>

        setInterval(updateByAJAX_dbData,1000);
        function updateByAJAX_dbData(){
            const xmlhttp=new XMLHttpRequest();
            xmlhttp.onreadystatechange=function(){
                if (this.readyState == 4 && this.status == 200) {
                    console.log(this.responseText);
                    document.getElementById("WaterLevel").innerHTML = this.responseText;
                }
            };
            xmlhttp.open("GET", "retrieve.php",true);
            xmlhttp.send();
        }
    </script>

    </section>
</body>

</html>

</html>