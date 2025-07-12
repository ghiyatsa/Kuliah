<?php
include 'connection.php';

$kode = $_GET['kode'];
$conn->query("DELETE FROM satuan WHERE kode_satuan='$kode'");
header("Location: satuan.php");