<?php
include 'db_connect.php';

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    // Validate and sanitize inputs
    if (!isset($_POST['kode']) || !isset($_POST['nama'])) {
        die("Required fields are missing");
    }

    $kode = $conn->real_escape_string(trim($_POST['kode']));
    $nama = $conn->real_escape_string(trim($_POST['nama']));

    if (empty($kode) || empty($nama)) {
        die("Fields cannot be empty");
    }

    // Prepare and execute statement to prevent SQL injection
    $stmt = $conn->prepare("UPDATE satuan SET nama_satuan = ? WHERE kode_satuan = ?");
    $stmt->bind_param("ss", $nama, $kode);

    if ($stmt->execute()) {
        $stmt->close();
        header("Location: satuan_list.php");
        exit();
    } else {
        echo "Error updating record: " . $stmt->error;
        $stmt->close();
    }
}
?>