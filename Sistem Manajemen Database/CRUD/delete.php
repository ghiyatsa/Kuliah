<?php
include 'connection.php';
$kode = $_GET['kode'];
$satuan = $_GET['satuan'];

$conn->query("DELETE FROM barang WHERE kode_barang='$kode' AND satuan='$satuan'");
header("Location: index.php");