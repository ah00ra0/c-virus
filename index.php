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
</head>
<body>

<h2>نوشتن و اضافه کردن در فایل (خواندن یک بار)</h2>

<textarea id="data" rows="5" cols="40" placeholder="متن خود را وارد کنید..."></textarea><br><br>

<button onclick="sendData()">اضافه کن</button>
<button onclick="add001()">001</button>
<button onclick="add002()">002</button>

<p id="status"></p>

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
