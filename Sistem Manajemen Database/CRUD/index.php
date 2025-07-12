<?php
include 'connection.php';
$data = $conn->query("SELECT barang.*, satuan.nama_satuan FROM barang JOIN satuan ON barang.satuan = satuan.kode_satuan");
?>
<!DOCTYPE html>
<html>

<head>
    <title>Latihan CRUD</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>

<body class="container py-5">
    <h2 class="mb-4">Data Barang</h2>
    <a href="create.php" class="btn btn-success mb-3">+ Tambah Barang</a>
    <a href="satuan.php" class="btn btn-primary mb-3">+ Tambah Satuan</a>
    <table class="table table-bordered table-striped">
        <thead class="table-dark">
            <tr>
                <th>No</th>
                <th>Nama</th>
                <th>Satuan</th>
                <th>Harga</th>
                <th>Stok</th>
                <th>Aksi</th>
            </tr>
        </thead>
        <tbody>
            <?php 
            $no = 1;
            while ($row = $data->fetch_assoc()): ?>
            <tr>
                <td><?= $no++ ?></td>
                <td><?= $row['nama_barang'] ?></td>
                <td><?= $row['nama_satuan'] ?></td>
                <td><?= number_format($row['harga']) ?></td>
                <td><?= $row['stok'] ?></td>
                <td>
                    <a href="update.php?kode=<?= $row['kode_barang'] ?>&satuan=<?= $row['satuan'] ?>"
                        class="btn btn-warning btn-sm">Edit</a>
                    <a href="delete.php?kode=<?= $row['kode_barang'] ?>&satuan=<?= $row['satuan'] ?>"
                        class="btn btn-danger btn-sm" onclick="return confirm('Yakin ingin menghapus?')">Hapus</a>
                </td>
            </tr>
            <?php endwhile; ?>
        </tbody>
    </table>
</body>

</html>