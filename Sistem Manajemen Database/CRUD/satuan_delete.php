<?php
include 'db_connect.php';

if (!isset($_GET['id']) || empty($_GET['id'])) {
    die("Invalid ID parameter");
}

$id = mysqli_real_escape_string($conn, $_GET['id']);


$stmt = $conn->prepare("DELETE FROM satuan WHERE kode_satuan = ?");
$stmt->bind_param("s", $id);

if ($stmt->execute()) {
    $stmt->close();
    header("Location: satuan_list.php");
    exit();
} else {
    $stmt->close();
    die("Error deleting record: " . $conn->error);
}
?>