<?php
$x = 10;
if ($x < 10) {
    echo "benar";
} else if ($x == 10) {
    echo "tepat!";
} else {
    echo "salah";
}
echo "<br>";

$warna = "merah";
switch ($warna) {
    case "merah":
        echo "Warna pilihan merah!";
        break;
    case "biru":
        echo "Warna pilihan biru!";
        break;
    default:
        echo "Tidak ada pilihan!";
}
?>