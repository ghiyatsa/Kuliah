<?php
include 'connection.php';

$kode = $_GET['kode'];
$satuan = $_GET['satuan'];
$data = $conn->query("SELECT * FROM barang WHERE kode_barang='$kode' AND satuan='$satuan'")->fetch_assoc();

if ($_POST) {
    $nama  = $_POST['nama_barang'];
    $harga = $_POST['harga'];
    $stok  = $_POST['stok'];

    $conn->query("UPDATE barang SET nama_barang='$nama', harga=$harga, stok=$stok WHERE kode_barang='$kode' AND satuan='$satuan'");
    header("Location: index.php");
}

$satuanList = $conn->query("SELECT * FROM satuan");
?>
<!DOCTYPE html>
<html>

<head>
    <title>Edit Barang</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>

<body class="container py-5">
    <h2 class="mb-4">Edit Barang</h2>
    <form method="POST">
        <div class="mb-3">
            <label class="form-label">Nama Barang</label>
            <input type="text" name="nama_barang" class="form-control" value="<?= $data['nama_barang'] ?>">
        </div>
        <div class="mb-3">
            <label class="form-label">Harga</label>
            <input type="number" name="harga" class="form-control" value="<?= $data['harga'] ?>">
        </div>
        <div class="mb-3">
            <label class="form-label">Stok</label>
            <input type="number" name="stok" class="form-control" value="<?= $data['stok'] ?>">
        </div>
        <button type="submit" class="btn btn-primary">Update</button>
        <a href="index.php" class="btn btn-secondary">Batal</a>
    </form>
</body>

</html>