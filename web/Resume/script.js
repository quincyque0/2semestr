document.addEventListener('DOMContentLoaded', function() {
    initDocumentUploadSystem();
    initTextSaveSystem();
    initPhotoUploadSystem();
    initPdfDownloadSystem();
    initPrintSystem();
  });
  
  function initDocumentUploadSystem() {
    const fileInput = document.getElementById('education-doc');
    if (!fileInput) return;
  
    const attachedFilesContainer = document.querySelector('.attached-files');
    let uploadedFiles = [];
    
    fileInput.addEventListener('change', function(e) {
      if (e.target.files && e.target.files.length > 0) {
        Array.from(e.target.files).forEach(file => {
          if (file.size > 5 * 1024 * 1024) {
            alert(`Файл "${file.name}" слишком большой. Максимальный размер: 5MB`);
            return;
          }
          
          uploadedFiles.push(file);
          displayUploadedFile(file);
        });
        fileInput.value = '';
      }
    });
    
    function displayUploadedFile(file) {
      const fileItem = document.createElement('div');
      fileItem.className = 'file-item';
      
      const fileIcon = document.createElement('span');
      fileIcon.className = 'file-icon';
      fileIcon.innerHTML = getFileIcon(file.type);
      
      const fileName = document.createElement('span');
      fileName.className = 'file-name';
      fileName.textContent = truncateFileName(file.name, 20);
      
      const fileSize = document.createElement('span');
      fileSize.className = 'file-size';
      fileSize.textContent = formatFileSize(file.size);
      
      const removeBtn = document.createElement('button');
      removeBtn.className = 'remove-btn';
      removeBtn.innerHTML = '&times;';
      removeBtn.title = 'Удалить';
      
      removeBtn.addEventListener('click', function() {
        uploadedFiles = uploadedFiles.filter(f => f.name !== file.name);
        fileItem.remove();
      });
      
      fileItem.appendChild(fileIcon);
      fileItem.appendChild(fileName);
      fileItem.appendChild(fileSize);
      fileItem.appendChild(removeBtn);
      
      attachedFilesContainer.appendChild(fileItem);
    }
    
    function getFileIcon(fileType) {
      const icons = {
        'application/pdf': '📄',
        'application/msword': '📝',
        'application/vnd.openxmlformats-officedocument.wordprocessingml.document': '📝',
        'image/jpeg': '🖼️',
        'image/png': '🖼️',
        'default': '📁'
      };
      return icons[fileType] || icons.default;
    }
    
    function truncateFileName(name, maxLength) {
      if (name.length <= maxLength) return name;
      const extension = name.split('.').pop();
      const baseName = name.substring(0, maxLength - extension.length - 3);
      return `${baseName}...${extension}`;
    }
    
    function formatFileSize(bytes) {
      if (bytes === 0) return '0 Bytes';
      const k = 1024;
      const sizes = ['Bytes', 'KB', 'MB', 'GB'];
      const i = Math.floor(Math.log(bytes) / Math.log(k));
      return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i];
    }
  }
  
  function initTextSaveSystem() {
    const editableFields = document.querySelectorAll('.redactable');
    if (!editableFields.length) return;
  
    editableFields.forEach(field => {
      const sectionTitle = field.previousElementSibling?.textContent.trim();
      if (!sectionTitle) return;
  
      const savedText = localStorage.getItem(`resume_${sectionTitle}`);
      if (savedText) {
        field.innerHTML = savedText;
      }
      
      field.addEventListener('input', function() {
        localStorage.setItem(`resume_${sectionTitle}`, this.innerHTML);
      });
    });
  }
  
  function initPhotoUploadSystem() {
    const changePhotoBtn = document.getElementById('changePhotoBtn');
    const photoUpload = document.getElementById('photoUpload');
    const profileImage = document.getElementById('profileImage');
    
    if (!changePhotoBtn || !photoUpload || !profileImage) return;
  
    const savedPhoto = localStorage.getItem('resume_profile_photo');
    if (savedPhoto) {
      profileImage.src = savedPhoto;
    }
    
    changePhotoBtn.addEventListener('click', () => {
      photoUpload.click();
    });
    
    photoUpload.addEventListener('change', (e) => {
      const file = e.target.files[0];
      if (!file) return;
  
      if (!file.type.match('image.*')) {
        alert('Пожалуйста, выберите изображение');
        return;
      }
      
      if (file.size > 2 * 1024 * 1024) {
        alert('Изображение слишком большое. Максимальный размер: 2MB');
        return;
      }
      
      const reader = new FileReader();
      reader.onload = (event) => {
        profileImage.src = event.target.result;
        localStorage.setItem('resume_profile_photo', event.target.result);
      };
      reader.readAsDataURL(file);
    });
  }
  
  function initPdfDownloadSystem() {
    const downloadBtn = document.getElementById('downloadPdfBtn');
    if (!downloadBtn) return;
  
    downloadBtn.addEventListener('click', async function() {
      const button = this;
      button.disabled = true;
      button.classList.add('loading');
      button.textContent = 'Генерация PDF...';
      
      try {
        // Создаем копию содержимого
        const element = document.getElementById('resumeContent');
        const clone = element.cloneNode(true);
        
        // Удаляем ненужные элементы
        clone.querySelector('.button-container')?.remove();
        clone.querySelectorAll('input[type="file"]').forEach(input => input.remove());
        clone.querySelectorAll('.change-photo-btn').forEach(btn => btn.remove());
        
        // Применяем стили для печати
        const printStyles = document.createElement('style');
        printStyles.textContent = `
          body { background: white; color: black; padding: 20px; }
          .resume-card { box-shadow: none; border: 1px solid #ddd; }
          .profile-img { border-color: #666; }
          .line { background-color: #666; }
        `;
        clone.prepend(printStyles);
        
        // Создаем временный элемент
        const tempDiv = document.createElement('div');
        tempDiv.appendChild(clone);
        document.body.appendChild(tempDiv);
        
        // Опции для генерации PDF
        const opt = {
          margin: 10,
          filename: 'Мое_резюме.pdf',
          image: { type: 'jpeg', quality: 0.98 },
          html2canvas: { 
            scale: 2,
            logging: true,
            useCORS: true,
            scrollX: 0,
            scrollY: 0
          },
          jsPDF: { 
            unit: 'mm', 
            format: 'a4', 
            orientation: 'portrait'
          }
        };
        
        // Генерируем PDF
        await html2pdf().set(opt).from(tempDiv).save();
        
        // Удаляем временный элемент
        document.body.removeChild(tempDiv);
        
      } catch (err) {
        console.error('Ошибка генерации PDF:', err);
        alert('Произошла ошибка при генерации PDF: ' + err.message);
      } finally {
        button.disabled = false;
        button.classList.remove('loading');
        button.textContent = 'Download PDF';
      }
    });
  }
  
  function initPrintSystem() {
    const printBtn = document.getElementById('printBtn');
    if (!printBtn) return;
  
    printBtn.addEventListener('click', function() {
      const button = this;
      button.disabled = true;
      button.textContent = 'Подготовка...';
      
      try {
        const element = document.getElementById('resumeContent');
        const clone = element.cloneNode(true);
        
        // Удаляем ненужные элементы
        clone.querySelector('.button-container')?.remove();
        clone.querySelectorAll('input[type="file"]').forEach(input => input.remove());
        clone.querySelectorAll('.change-photo-btn').forEach(btn => btn.remove());
        
        // Применяем стили для печати
        const printStyles = document.createElement('style');
        printStyles.textContent = `
          @media print {
            body { background: white; color: black; padding: 20px; }
            .resume-card { box-shadow: none; border: 1px solid #ddd; }
            .profile-img { border-color: #666; }
            .line { background-color: #666; }
          }
        `;
        clone.prepend(printStyles);
        
        // Открываем новое окно для печати
        const printWindow = window.open('', '_blank');
        printWindow.document.write('<!DOCTYPE html><html><head><title>Мое резюме</title></head><body>');
        printWindow.document.write(clone.outerHTML);
        printWindow.document.write('</body></html>');
        printWindow.document.close();
        
        // Даем время на загрузку и печатаем
        setTimeout(() => {
          printWindow.print();
          button.disabled = false;
          button.textContent = 'Print Document';
        }, 500);
        
      } catch (err) {
        console.error('Ошибка печати:', err);
        button.disabled = false;
        button.textContent = 'Print Document';
        alert('Произошла ошибка при подготовке к печати');
      }
    });
  }