<?php
include 'db_connect.php';
$id = $_GET['id'];
$sql = "SELECT * FROM satuan WHERE kode_satuan = '$id'";
$result = $conn->query($sql);
if (!$result) {
    die("Query error: " . $conn->error);
}
$row = $result->fetch_assoc();
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Input Data Satuan</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
        }

        .form-container {
            max-width: 400px;
            margin: auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }

        .form-container h2 {
            text-align: center;
            margin-bottom: 20px;
        }

        .form-group {
            margin-bottom: 15px;
        }

        .form-group label {
            display: block;
            margin-bottom: 5px;
        }

        .form-group input {
            width: calc(100% - 22px);
            padding: 10px;
            border: 1px solid #ccc;
            border-radius: 5px;
        }

        .form-group button {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        .form-group button:hover {
            background-color: #45a049;
        }

        .back-button {
            padding: 10px 15px;
            background-color: #ed0e0e;
            color: white;
            border: none;
            cursor: pointer;
        }

        .back-button:hover {
            background-color: #7d0418;
        }
    </style>
</head>

<body>
    <div class="form-container">
        <h2>Edit Data Satuan</h2>
        <form action="satuan_update.php" method="post">
            <div class="form-group">
                <label for="kode">Kode</label>
                <input type="text" id="kode" name="kode" value="<?php echo $row['kode_satuan']; ?>" required>
            </div>
            <div class="form-group">
                <label for="nama">Nama</label>
                <input type="text" id="nama" name="nama" value="<?php echo $row['nama_satuan']; ?>" required>
            </div>
            <div class="form-group">
                <button type="submit">Update</button>
                <br><br>
            </div>
        </form>
        <a href="satuan_list.php"><button class="back-button">Kembali</button></a>
    </div>
</body>

</html>