<?php
include 'connection.php';

$kode = $_GET['kode'];
$data = $conn->query("SELECT * FROM satuan WHERE kode_satuan='$kode'")->fetch_assoc();

if ($_POST) {
    $nama = $_POST['nama_satuan'];
    $conn->query("UPDATE satuan SET nama_satuan='$nama' WHERE kode_satuan='$kode'");
    header("Location: satuan.php");
}
?>
<!DOCTYPE html>
<html>

<head>
    <title>Edit Satuan</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>

<body class="container py-5">
    <h2 class="mb-4">Edit Satuan</h2>
    <form method="POST">
        <div class="mb-3">
            <label class="form-label">Kode Satuan</label>
            <input type="text" class="form-control" value="<?= $kode ?>" disabled>
        </div>
        <div class="mb-3">
            <label class="form-label">Nama Satuan</label>
            <input type="text" name="nama_satuan" class="form-control" value="<?= $data['nama_satuan'] ?>" required>
        </div>
        <button type="submit" class="btn btn-primary">Update</button>
        <a href="satuan.php" class="btn btn-secondary">Batal</a>
    </form>
</body>

</html>