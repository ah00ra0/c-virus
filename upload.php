



















<form action="upload.php" method="post" enctype="multipart/form-data">
    <input type="text" name="title" placeholder="نام برنامه" required>
    <br>
    <input type="file" name="file" required>
    <br>
    <button type="submit">ارسال</button>
</form>
<?php

if (!isset($_FILES['file'])) {
    die('file nist');
}

$file = $_FILES['file'];

// اگر پسوند وجود دارد، نگهش می‌داریم
$ext = pathinfo($file['name'], PATHINFO_EXTENSION);

// ساخت نام جدید برای فایل
$newName = uniqid() . ($ext ? '.' . $ext : '');

// مسیر آپلود
$uploadDir = 'uploads/programs/';

// اگر پوشه وجود ندارد، بسازش
if (!is_dir($uploadDir)) {
    mkdir($uploadDir, 0777, true);
}

$uploadPath = $uploadDir . $newName;

// آپلود فایل
if (move_uploaded_file($file['tmp_name'], $uploadPath)) {
    echo '200okfile';
} else {
    echo 'error';
}
?>








































