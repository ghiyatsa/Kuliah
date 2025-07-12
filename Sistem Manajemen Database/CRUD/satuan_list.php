<?php
include 'db_connect.php';
$sql = "SELECT * FROM satuan";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <title>Daftar Satuan</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 20px;
        }

        table,
        th,
        td {
            border: 1px solid #ccc;
        }

        th,
        td {
            padding: 10px;
            text-align: left;
        }

        th {
            background-color: #f4f4f4;
        }

        .button-container {
            margin-bottom: 10px;
        }

        .add-button {
            padding: 10px 15px;
            background-color: #4CAF50;
            color: white;
            border: none;
            cursor: pointer;
        }

        .back-button {
            padding: 10px 15px;
            background-color: #ed0e0e;
            color: white;
            border: none;
            cursor: pointer;
        }

        .add-button:hover {
            background-color: #45a049;
        }

        .back-button:hover {
            background-color: #7d0418;
        }
    </style>
</head>

<body>
    <h1>Daftar Satuan</h1>

    <div class="button-container">
        <a href="satuan_tambah.php"><button class="add-button">Tambah Data</button></a>
        <a href="index.php"><button class="back-button">Kembali</button></a>
    </div>

    <table>
        <thead>
            <tr>
                <th>No</th>
                <th>Kode</th>
                <th>Nama</th>
                <th>Aksi</th>
            </tr>
        </thead>
        <tbody>
            <?php
            if ($result->num_rows > 0) {
                $no = 1;
                while ($row = $result->fetch_assoc()) {
                    echo "<tr>";
                    echo "<td>" . $no++ . "</td>";
                    echo "<td>" . $row['kode_satuan'] . "</td>";
                    echo "<td>" . $row['nama_satuan'] . "</td>";
                    echo "<td><a href='satuan_edit.php?id=" . $row['kode_satuan'] . "'><button>Edit</button></a> | <a href='satuan_delete.php?id=" . $row['kode_satuan'] . "'><button>Hapus</button></a>";
                    echo "</tr>";
                }
            }
            ?>
        </tbody>
    </table>
</body>

</html>