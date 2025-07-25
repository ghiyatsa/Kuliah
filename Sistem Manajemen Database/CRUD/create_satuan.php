<?php
include 'connection.php';

if ($_POST) {
    $kode = $_POST['kode_satuan'];
    $nama = $_POST['nama_satuan'];

    $conn->query("INSERT INTO satuan VALUES('$kode', '$nama')");
    header("Location: satuan.php");
}
?>
<!DOCTYPE html>
<html>

<head>
    <title>Tambah Satuan</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>

<body class="container py-5">
    <h2 class="mb-4">Tambah Satuan</h2>
    <form method="POST">
        <div class="mb-3">
            <label class="form-label">Kode Satuan</label>
            <input type="text" name="kode_satuan" class="form-control" maxlength="3" required>
        </div>
        <div class="mb-3">
            <label class="form-label">Nama Satuan</label>
            <input type="text" name="nama_satuan" class="form-control" required>
        </div>
        <button type="submit" class="btn btn-primary">Simpan</button>
        <a href="satuan.php" class="btn btn-secondary">Batal</a>
    </form>
</body>

</html>