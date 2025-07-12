document.addEventListener("DOMContentLoaded", () => {
  const API_URL = "api.php";

  // Elemen-elemen DOM
  const form = document.getElementById("dataForm");
  const tableBody = document.querySelector("#dataTable tbody");
  const editIdInput = document.getElementById("edit-id");
  const clearBtn = document.getElementById("clearBtn");
  const submitBtn = document.getElementById("submitBtn");

  // Input & pesan error
  const nameInput = document.getElementById("name");
  const nameError = document.getElementById("name-error");
  const passwordInput = document.getElementById("password");
  const verifyPasswordInput = document.getElementById("verify-password");
  const showPasswordCheckbox = document.getElementById(
    "show-password-checkbox"
  );
  const pwError = document.getElementById("pw-error");
  const prefError = document.getElementById("pref-error");

  const getInputValue = (id) => document.getElementById(id).value;

  const showError = (el) => (el.style.display = "block");
  const hideError = (el) => (el.style.display = "none");

  const getCheckedValues = (selector) =>
    Array.from(document.querySelectorAll(selector + ":checked")).map(
      (el) => el.value
    );

  const resetCheckboxes = (selector) =>
    document.querySelectorAll(selector).forEach((el) => (el.checked = false));

  // Render tabel dari data backend
  const renderTable = async () => {
    try {
      const res = await fetch(`${API_URL}?action=get_all`);
      const { success, data } = await res.json();

      tableBody.innerHTML = "";

      if (success && data.length) {
        data.forEach(({ id, name, gender, submission_date }) => {
          const row = tableBody.insertRow();
          row.insertCell().textContent = `${name} (${gender})`;
          row.insertCell().textContent = new Date(
            submission_date
          ).toLocaleDateString("id-ID");

          const actionCell = row.insertCell();
          actionCell.className = "action-links";

          actionCell.appendChild(createLink("Edit", () => handleEdit(id)));
          actionCell.appendChild(
            createLink("Hapus", () => handleDelete(id), "delete")
          );
        });
      } else {
        const row = tableBody.insertRow();
        const cell = row.insertCell();
        cell.colSpan = 3;
        cell.textContent = "Belum ada data yang tersimpan.";
        cell.style.textAlign = "center";
      }
    } catch (err) {
      console.error(err);
      alert("Gagal memuat data dari server.");
    }
  };

  const createLink = (text, onClick, className = "") => {
    const link = document.createElement("a");
    link.textContent = text;
    link.href = "#";
    if (className) link.classList.add(className);
    link.onclick = (e) => {
      e.preventDefault();
      onClick();
    };
    return link;
  };

  // Validasi form
  const validateForm = () => {
    let isValid = true;

    nameInput.value.trim() === ""
      ? (showError(nameError), (isValid = false))
      : hideError(nameError);
    passwordInput.value !== verifyPasswordInput.value
      ? (showError(pwError), (isValid = false))
      : hideError(pwError);
    getCheckedValues('input[name="preferences"]').length === 0
      ? (showError(prefError), (isValid = false))
      : hideError(prefError);

    return isValid;
  };

  // Submit form (create/update)
  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!validateForm()) return;

    const payload = {
      id: editIdInput.value || null,
      name: getInputValue("name"),
      address: getInputValue("address"),
      zipCode: getInputValue("zip-code"),
      country: getInputValue("country"),
      gender: document.querySelector('input[name="gender"]:checked')?.value,
      preferences: getCheckedValues('input[name="preferences"]'),
      phone: getInputValue("phone"),
      email: getInputValue("email"),
      password: passwordInput.value,
    };

    try {
      const res = await fetch(API_URL, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(payload),
      });
      const result = await res.json();
      alert(result.message);
      if (result.success) {
        renderTable();
        handleClear();
      }
    } catch (err) {
      console.error(err);
      alert("Gagal mengirim data ke server.");
    }
  };

  // Ambil data & isi form saat edit
  const handleEdit = async (id) => {
    try {
      const res = await fetch(`${API_URL}?action=get_single&id=${id}`);
      const { success, data } = await res.json();
      if (!success) return;

      Object.assign(editIdInput, { value: data.id });
      nameInput.value = data.name;
      document.getElementById("address").value = data.address;
      document.getElementById("zip-code").value = data.zip_code;
      document.getElementById("country").value = data.country;
      document.querySelector(
        `input[name="gender"][value="${data.gender}"]`
      ).checked = true;

      resetCheckboxes('input[name="preferences"]');
      JSON.parse(data.preferences || "[]").forEach((pref) => {
        const cb = document.querySelector(
          `input[name="preferences"][value="${pref}"]`
        );
        if (cb) cb.checked = true;
      });

      document.getElementById("phone").value = data.phone;
      document.getElementById("email").value = data.email;
      passwordInput.value = "";
      verifyPasswordInput.value = "";

      passwordInput.removeAttribute("required");
      verifyPasswordInput.removeAttribute("required");

      submitBtn.textContent = "EDIT";
      window.scrollTo({ top: 0, behavior: "smooth" });
      nameInput.focus();
    } catch (err) {
      console.error("Error saat edit:", err);
    }
  };

  // Hapus data
  const handleDelete = async (id) => {
    if (!confirm("Apakah Anda yakin ingin menghapus data ini?")) return;

    try {
      const res = await fetch(`${API_URL}?id=${id}`, { method: "DELETE" });
      const result = await res.json();
      alert(result.message);
      if (result.success) renderTable();
    } catch (err) {
      console.error("Gagal menghapus data:", err);
    }
  };

  // Reset form
  const handleClear = () => {
    form.reset();
    editIdInput.value = "";

    [nameError, pwError, prefError].forEach(hideError);

    passwordInput.setAttribute("required", "required");
    verifyPasswordInput.setAttribute("required", "required");

    submitBtn.textContent = "SEND";
  };

  // Toggle visibilitas password
  const togglePasswordVisibility = () => {
    const type = showPasswordCheckbox.checked ? "text" : "password";
    passwordInput.type = type;
    verifyPasswordInput.type = type;
  };

  // Event listeners
  form.addEventListener("submit", handleSubmit);
  clearBtn.addEventListener("click", handleClear);
  showPasswordCheckbox.addEventListener("change", togglePasswordVisibility);

  // Inisialisasi tabel
  renderTable();
});
