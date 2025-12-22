<?php
$file = __DIR__ . "/man.txt";

/* =======================
   READ ONCE
   ======================= */
if (isset($_GET["read"]) && $_GET["read"] == "1") {
    if (file_exists($file)) {
        // خواندن محتوا
        $content = file_get_contents($file);
        echo $content;

        // بعد از خواندن → پاک کردن محتوا
        file_put_contents($file, "");
    }
    exit;
}

/* =======================
   APPEND DATA
   ======================= */
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (isset($_POST["data"])) {
        // اضافه کردن متن به فایل
        file_put_contents($file, $_POST["data"] . PHP_EOL, FILE_APPEND);
        echo "saved";
        exit;
    }
}
?>

<!DOCTYPE html>
<html lang="fa">
<head>
    <meta charset="UTF-8">
    <title>Append & Read Once</title>
    
<style>
body {
    margin: 0;
    height: 100vh;
    background: linear-gradient(135deg, #0f2027, #203a43, #2c5364);
    display: flex;
    align-items: center;
    justify-content: center;
    color: #fff;
    font-family: 'Segoe UI', Tahoma, sans-serif;
    flex-direction: column;
}

.glass {
    width: 420px;
    padding: 30px;
    background: rgba(20,20,20,0.75);
    border-radius: 16px;
    border: 1px solid rgba(255,255,255,0.1);
    backdrop-filter: blur(12px);
    display: flex;
    flex-direction: column;
    gap: 15px;
    box-shadow: 0 8px 30px rgba(0,0,0,0.5);
}

textarea {
    width: 100%;
    height: 100px;
    padding: 12px;
    resize: none;
    background: rgba(0,0,0,0.6);
    color: #fff;
    border: 1px solid rgba(255,255,255,0.2);
    border-radius: 12px;
    outline: none;
    font-family: 'Roboto Mono', monospace;
    transition: 0.3s;
}

textarea:focus {
    border-color: #00ffc6;
    box-shadow: 0 0 10px rgba(0, 255, 198, 0.5);
}

button {
    flex: 1 1 calc(25% - 10px);
    padding: 10px;
    background: linear-gradient(145deg, rgba(0,255,198,0.2), rgba(0,255,198,0.05));
    color: #00ffc6;
    border: 1px solid rgba(0,255,198,0.5);
    border-radius: 12px;
    cursor: pointer;
    transition: 0.3s;
    min-width: 80px;
}

button:hover {
    background: rgba(0,255,198,0.3);
    box-shadow: 0 0 15px rgba(0,255,198,0.5);
    transform: translateY(-2px);
}

#status {
    text-align: center;
    font-size: 13px;
    color: #00ffc6;
}

h1, h2 {
    text-align: center;
    color: #00ffc6;
    text-shadow: 0 0 8px rgba(0,255,198,0.7);
}
body {
    margin: 0;
    height: 100vh;
    background: linear-gradient(135deg, #0f2027, #203a43, #2c5364);
    display: flex;
    align-items: center;
    justify-content: center;
    color: #fff;
    font-family: 'Segoe UI', Tahoma, sans-serif;
    flex-direction: column;
}

.glass {
    width: 420px;
    padding: 30px;
    background: rgba(20,20,20,0.75);
    border-radius: 16px;
    border: 1px solid rgba(255,255,255,0.1);
    backdrop-filter: blur(12px);
    display: flex;
    flex-direction: column;
    gap: 15px;
    box-shadow: 0 8px 30px rgba(0,0,0,0.5);
}

textarea {
    width: 100%;
    height: 100px;
    padding: 12px;
    resize: none;
    background: rgba(0,0,0,0.6);
    color: #fff;
    border: 1px solid rgba(255,255,255,0.2);
    border-radius: 12px;
    outline: none;
    font-family: 'Roboto Mono', monospace;
    transition: 0.3s;
}

textarea:focus {
    border-color: #00ffc6;
    box-shadow: 0 0 10px rgba(0, 255, 198, 0.5);
}

button {
    flex: 1 1 calc(25% - 10px);
    padding: 10px;
    background: linear-gradient(145deg, rgba(0,255,198,0.2), rgba(0,255,198,0.05));
    color: #00ffc6;
    border: 1px solid rgba(0,255,198,0.5);
    border-radius: 12px;
    cursor: pointer;
    transition: 0.3s;
    min-width: 80px;
}

button:hover {
    background: rgba(0,255,198,0.3);
    box-shadow: 0 0 15px rgba(0,255,198,0.5);
    transform: translateY(-2px);
}

#status {
    text-align: center;
    font-size: 13px;
    color: #00ffc6;
}

h1, h2 {
    text-align: center;
    color: #00ffc6;
    text-shadow: 0 0 8px rgba(0,255,198,0.7);
}

</style>

</head>
<body><div class="h">
    <h1 class="glass h1-glow">AHOORA</h1><br>
</div>
<div class="glass" id="man">
<h2>Append & Read Once</h2>

<textarea id="data" rows="5" cols="40" placeholder="متن خود را وارد کنید..."></textarea><br><br>
  <div class="buttons">
<button onclick="sendData()">اضافه کن</button>
<button onclick="add001()">speak</button>
<button onclick="add002()">box</button>
<button onclick="add003()">mute</button>
<button onclick="addCustom()">Custom</button>



</div>

<p id="status"></p>
</div>

<script>
function sendData() {
    let text = document.getElementById("data").value;
    appendData(text);
}

function add001() {
     let text = prompt("Please enter your text"); // گرفتن متن از کاربر
    if (text) {
        appendData("001:" + text); // اضافه کردن 001: جلوی متن
    }
}

function add002() {
    appendData("002");
}
function add003() {
    appendData("003");
}

function appendData(text) {
    fetch("", {
        method: "POST",
        headers: {"Content-Type": "application/x-www-form-urlencoded"},
        body: "data=" + encodeURIComponent(text)
    })
    .then(() => {
        document.getElementById("status").innerText = "✅ add";
        document.getElementById("data").value = "";
    });
}
function addCustom() {
    let text = prompt("متن خود را وارد کنید:");
    if (text) { // اگر کاربر چیزی وارد کرد
        appendData(text);
    }
}

</script>

</body>
</html>


