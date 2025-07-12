<?php
include 'connection.php';
$data = $conn->query("SELECT * FROM satuan");
?>
<!DOCTYPE html>
<html>

<head>
    <title>Data Satuan</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css" rel="stylesheet">
</head>

<body class="container py-5">
    <h2 class="mb-4">Data Satuan</h2>
    <a href="create_satuan.php" class="btn btn-success mb-3">+ Tambah Satuan</a>
    <a href="index.php" class="btn btn-secondary mb-3">← Kembali ke Barang</a>
    <table class="table table-bordered table-striped">
        <thead class="table-dark">
            <tr>
                <th>Nama Satuan</th>
                <th>Aksi</th>
            </tr>
        </thead>
        <tbody>
            <?php while ($row = $data->fetch_assoc()): ?>
            <tr>
                <td><?= $row['nama_satuan'] ?></td>
                <td>
                    <a href="update_satuan.php?kode=<?= $row['kode_satuan'] ?>" class="btn btn-warning btn-sm">Edit</a>
                    <a href="delete_satuan.php?kode=<?= $row['kode_satuan'] ?>" class="btn btn-danger btn-sm"
                        onclick="return confirm('Yakin ingin menghapus?')">Hapus</a>
                </td>
            </tr>
            <?php endwhile; ?>
        </tbody>
    </table>
</body>

</html>