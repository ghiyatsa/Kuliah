<!DOCTYPE html>
<html lang="id">

<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>UAS PEMROGRAMAN WEB</title>
    <link rel="stylesheet" href="style.css" />
</head>

<body>
    <header>
        <h1>UAS PEMROGRAMAN WEB</h1>
        <h2>Baris Ganjil</h2>
    </header>

    <main class="container">
        <!-- Kolom Kiri: Formulir -->
        <div class="form-wrapper">
            <div class="form-container">
                <form id="dataForm" novalidate>
                    <input type="hidden" id="edit-id" />

                    <div class="form-group">
                        <label for="name">Name<span class="required">*</span></label>
                        <input type="text" id="name" name="name" required placeholder="Please enter your name" />
                        <small id="name-error" class="error-message" style="display:none;">Please enter your
                            name!</small>
                    </div>

                    <div class="form-group">
                        <label for="address">Address</label>
                        <textarea id="address" name="address" rows="3"
                            placeholder="Please enter your address"></textarea>
                    </div>

                    <div class="form-group">
                        <label for="zip-code">Zip Code<span class="required">*</span></label>
                        <input type="text" id="zip-code" name="zip-code" required pattern="\d*"
                            title="Harus berupa angka" />
                    </div>

                    <div class="form-group">
                        <label for="country">Country<span class="required">*</span></label>
                        <select id="country" name="country" required>
                            <option value="" disabled selected>Please select...</option>
                            <option value="Indonesia">Indonesia</option>
                            <option value="Malaysia">Malaysia</option>
                            <option value="Singapore">Singapore</option>
                            <option value="Thailand">Thailand</option>
                        </select>
                    </div>

                    <div class="form-group">
                        <label>Gender<span class="required">*</span></label>
                        <div class="radio-group">
                            <label><input type="radio" name="gender" value="Male" required /> Male</label>
                            <label><input type="radio" name="gender" value="Female" /> Female</label>
                        </div>
                    </div>

                    <div class="form-group">
                        <label>Preferences<span class="required">*</span></label>
                        <div class="checkbox-group">
                            <label><input type="checkbox" name="preferences" value="Red" /> Red</label>
                            <label><input type="checkbox" name="preferences" value="Green" /> Green</label>
                            <label><input type="checkbox" name="preferences" value="Blue" /> Blue</label>
                        </div>
                        <small id="pref-error" class="error-message" style="display:none;">Please select at least one
                            preference.</small>
                    </div>

                    <div class="form-group">
                        <label for="phone">Phone<span class="required">*</span></label>
                        <input type="tel" id="phone" name="phone" required pattern="[0-9]+" title="Hanya boleh angka" />
                    </div>

                    <div class="form-group">
                        <label for="email">Email<span class="required">*</span></label>
                        <input type="email" id="email" name="email" required />
                    </div>

                    <div class="form-group">
                        <label for="password">Password (6-8 characters)<span class="required">*</span></label>
                        <input type="password" id="password" name="password" required minlength="6" maxlength="8" />
                    </div>

                    <div class="form-group">
                        <label for="verify-password">Verify Password<span class="required">*</span></label>
                        <input type="password" id="verify-password" name="verify-password" required />
                        <small id="pw-error" class="error-message" style="display:none;">Passwords do not match.</small>
                    </div>

                    <div class="form-group form-group-inline">
                        <input type="checkbox" id="show-password-checkbox" />
                        <label for="show-password-checkbox" class="show-password-label">Show Password</label>
                    </div>

                    <div class="form-buttons">
                        <button type="submit" id="submitBtn">SEND</button>
                        <button type="button" id="clearBtn">CLEAR</button>
                    </div>
                </form>
            </div>
            <div class="nim form-container">
                <span>230</span>
                <span>170</span>
                <span>162</span>
            </div>
        </div>

        <!-- Kolom Kanan: List Data -->
        <div class="list-wrapper">
            <div class="list-container">
                <h3>List Data</h3>
                <div class="table-responsive">
                    <table id="dataTable">
                        <thead>
                            <tr>
                                <th>Nama</th>
                                <th>Tanggal</th>
                                <th>Aksi</th>
                            </tr>
                        </thead>
                        <tbody>
                            <!-- Data akan diisi oleh JavaScript -->
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </main>

    <script src="script.js"></script>
</body>

</html>