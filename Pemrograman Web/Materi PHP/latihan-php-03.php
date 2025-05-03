<?php
$a = 1;
while ($a < 6) {
    echo $a;
    $a++;
}
echo "<br>";

$b = 1;
while ($b < 6) {
    if ($b == 3) break;
    echo $b;
    $b++;
}
echo "<br>";

$c = 1;
do {
    echo $c;
    $c++;
} while ($c < 6);
echo "<br>";

$d = 1;
do {
    if ($d == 3) break;
    echo $d;
    $d++;
} while ($d < 6);
echo "<br>";

for ($e = 1; $e <= 10; $e++) {
    echo "Nomor: $e<br>";
}
echo "<br>";

for ($f = 0; $f <= 10; $f++) {
    if ($f == 3) break;
    echo "Nomor: $f<br>";
}
echo "<br>";

$kota = array(
    "lhokseumawe",
    "medan",
    "jakarta"
);

foreach ($kota as $g) {
    echo "$g<br>";
}
?>