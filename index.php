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
* {
    box-sizing: border-box;
    font-family: "Segoe UI", Tahoma, sans-serif;
}

body {
    margin: 0;
    height: 100vh;
    background: linear-gradient(135deg, #000, #222);
    display: flex;
    align-items: center;
    justify-content: center;
    color: #fff;
    flex-direction: column;  /* مهم */
 
}

/* Glass Box */
.glass {
    width: 420px;
    padding: 30px;
    background: rgba(255,255,255,0.08);
    backdrop-filter: blur(14px);
    -webkit-backdrop-filter: blur(14px);
    border-radius: 18px;
    border: 1px solid rgba(255,255,255,0.15);
    box-shadow: 0 10px 35px rgba(0,0,0,0.6);

    /* مهم‌ترین قسمت */
    display: flex;
    flex-direction: column;
    gap: 15px;
}

/* Title */
.glass h2 {
    margin: 0 0 10px;
    text-align: center;
    font-weight: 300;
}

/* Textarea */
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
}

.buttons {
    display: flex;
    flex-wrap: wrap;       /* اجازه می‌دهد دکمه‌ها به ردیف بعدی بروند */
    gap: 10px;             /* فاصله بین دکمه‌ها */
    justify-content: center; /* وسط چین شدن دکمه‌ها */
}

button {
    flex: 1 1 calc(25% - 10px); /* حداکثر ۴ دکمه در یک ردیف */
    padding: 10px;
    background: rgba(255,255,255,0.15);
    color: #fff;
    border: 1px solid rgba(255,255,255,0.25);
    border-radius: 12px;
    cursor: pointer;
    transition: 0.3s;
    min-width: 80px; /* برای موبایل یا زمانی که تعداد دکمه کمتر از ۴ است */
}

button:hover {
    background: rgba(255,255,255,0.35);
}

#status {
    text-align: center;
    font-size: 13px;
    color: #7CFF7C;
}


#man {
    animation: man 2.5s ease-in-out infinite;
}

@keyframes man {
    0% {
        text-shadow: 0 0 5px rgba(255,255,255,0.3);
        box-shadow: 0 0 10px rgba(255,255,255,0.15);
        opacity: 0.8;
    }
    50% {
        text-shadow: 0 0 20px rgba(255,255,255,0.9);
        box-shadow: 0 0 30px rgba(255,255,255,0.4);
        opacity: 1;
    }
    100% {
        text-shadow: 0 0 5px rgba(255,255,255,0.3);
        box-shadow: 0 0 10px rgba(255,255,255,0.15);
        opacity: 0.8;
    }
}


.h1-glow {
    position: relative;
    padding: 20px 40px;
    border-radius: 16px;
    background: rgba(255,255,255,0.08);
    border: 1px solid rgba(255,255,255,0.15);
    box-shadow: 0 8px 25px rgba(0,0,0,0.4);
    color: #fff;
    overflow: hidden; /* مهم برای clip کردن افکت */
}

/* خط برق */
.h1-glow::after {
    content: "";
    position: absolute;
    top: -50%;
    left: -50%;
    width: 200%;
    height: 200%;
    background: linear-gradient(
        120deg,
        rgba(255,255,255,0.0) 0%,
        rgba(255,255,255,0.6) 50%,
        rgba(255,255,255,0.0) 100%
    );
    transform: rotate(45deg);
    animation: shine 2s linear infinite;
}

/* حرکت نور */
@keyframes shine {
    0% {
        transform: translateX(-100%) rotate(45deg);
    }
    100% {
        transform: translateX(100%) rotate(45deg);
    }
}
.h{
     text-align: center;
    
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


</div>

<p id="status"></p>
</div>

<script>
function sendData() {
    let text = document.getElementById("data").value;
    appendData(text);
}

function add001() {
    appendData("001");
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
</script>

</body>
</html>
