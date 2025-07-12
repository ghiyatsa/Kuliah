<?php
require_once 'connection.php';
header('Content-Type: application/json');

$method = $_SERVER['REQUEST_METHOD'];
$action = $_GET['action'] ?? '';

// Fungsi untuk merespon dalam format JSON
function respond($success, $message = '', $data = null) {
    echo json_encode([
        'success' => $success,
        'message' => $message,
        'data' => $data
    ]);
    exit;
}

// Ambil semua data
function getAll($link) {
    $sql = "SELECT id, name, gender, submission_date FROM registrations ORDER BY id DESC";
    $result = mysqli_query($link, $sql);
    $data = mysqli_fetch_all($result, MYSQLI_ASSOC);
    respond(true, '', $data);
}

// Ambil data tunggal berdasarkan ID
function getSingle($link, $id) {
    $sql = "SELECT * FROM registrations WHERE id = ?";
    if ($stmt = mysqli_prepare($link, $sql)) {
        mysqli_stmt_bind_param($stmt, "i", $id);
        mysqli_stmt_execute($stmt);
        $result = mysqli_stmt_get_result($stmt);
        $data = mysqli_fetch_assoc($result);
        respond(true, '', $data);
    } else {
        respond(false, 'Gagal mengambil data.');
    }
}

// Tambah data baru
function create($link, $input) {
    $preferencesJson = json_encode($input['preferences']);
    $submissionDate = date('Y-m-d');
    $passwordHash = password_hash($input['password'], PASSWORD_DEFAULT);

    $sql = "INSERT INTO registrations (name, address, zip_code, country, gender, preferences, phone, email, password, submission_date)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    if ($stmt = mysqli_prepare($link, $sql)) {
        mysqli_stmt_bind_param($stmt, "ssssssssss",
            $input['name'],
            $input['address'],
            $input['zipCode'],
            $input['country'],
            $input['gender'],
            $preferencesJson,
            $input['phone'],
            $input['email'],
            $passwordHash,
            $submissionDate
        );
        if (mysqli_stmt_execute($stmt)) {
            respond(true, 'Data berhasil disimpan.');
        }
    }
    respond(false, 'Gagal menyimpan data.');
}

// Perbarui data berdasarkan ID
function update($link, $input) {
    $preferencesJson = json_encode($input['preferences']);

    $sql = "UPDATE registrations 
            SET name=?, address=?, zip_code=?, country=?, gender=?, preferences=?, phone=?, email=? 
            WHERE id=?";

    if ($stmt = mysqli_prepare($link, $sql)) {
        mysqli_stmt_bind_param($stmt, "ssssssssi",
            $input['name'],
            $input['address'],
            $input['zipCode'],
            $input['country'],
            $input['gender'],
            $preferencesJson,
            $input['phone'],
            $input['email'],
            $input['id']
        );
        if (mysqli_stmt_execute($stmt)) {
            respond(true, 'Data berhasil diperbarui.');
        }
    }
    respond(false, 'Gagal memperbarui data.');
}

// Hapus data berdasarkan ID
function delete($link, $id) {
    $sql = "DELETE FROM registrations WHERE id = ?";
    if ($stmt = mysqli_prepare($link, $sql)) {
        mysqli_stmt_bind_param($stmt, "i", $id);
        if (mysqli_stmt_execute($stmt)) {
            respond(true, 'Data berhasil dihapus.');
        }
    }
    respond(false, 'Gagal menghapus data.');
}

// Routing utama
switch ($method) {
    case 'GET':
        if ($action === 'get_all') {
            getAll($link);
        } elseif ($action === 'get_single' && isset($_GET['id'])) {
            getSingle($link, (int)$_GET['id']);
        } else {
            respond(false, 'Aksi GET tidak dikenali.');
        }
        break;

    case 'POST':
        $input = json_decode(file_get_contents('php://input'), true);
        if (!$input) {
            respond(false, 'Data input tidak valid.');
        }

        if (!empty($input['id'])) {
            update($link, $input);
        } else {
            create($link, $input);
        }
        break;

    case 'DELETE':
        if (isset($_GET['id'])) {
            delete($link, (int)$_GET['id']);
        } else {
            respond(false, 'ID tidak ditemukan untuk penghapusan.');
        }
        break;

    default:
        respond(false, 'Metode tidak didukung.');
}

mysqli_close($link);