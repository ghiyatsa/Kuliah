<?php
include 'connection.php';

if ($_POST) {
    $kode   = $_POST['kode_barang'];
    $nama   = $_POST['nama_barang'];
    $satuan = $_POST['satuan'];
    $harga  = $_POST['harga'];
    $stok   = $_POST['stok'];

    $conn->query("INSERT INTO barang VALUES('$kode', '$nama', '$satuan', $harga, $stok)");
    header("Location: index.php");
}

$satuanList = $conn->query("SELECT * FROM satuan");
?>
<!DOCTYPE html>
<html>

<head>
    <title>Tambah Barang</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>

<body class="container py-5">
    <h2 class="mb-4">Tambah Barang</h2>
    <form method="POST">
        <div class="mb-3">
            <label class="form-label">Kode Barang</label>
            <input type="text" name="kode_barang" class="form-control" required>
        </div>
        <div class="mb-3">
            <label class="form-label">Nama Barang</label>
            <input type="text" name="nama_barang" class="form-control">
        </div>
        <div class="mb-3">
            <label class="form-label">Satuan</label>
            <select name="satuan" class="form-select">
                <?php while ($s = $satuanList->fetch_assoc()): ?>
                <option value="<?= $s['kode_satuan'] ?>"><?= $s['nama_satuan'] ?></option>
                <?php endwhile; ?>
            </select>
        </div>
        <div class="mb-3">
            <label class="form-label">Harga</label>
            <input type="number" name="harga" class="form-control">
        </div>
        <div class="mb-3">
            <label class="form-label">Stok</label>
            <input type="number" name="stok" class="form-control">
        </div>
        <button type="submit" class="btn btn-primary">Simpan</button>
        <a href="index.php" class="btn btn-secondary">Batal</a>
    </form>
</body>

</html>