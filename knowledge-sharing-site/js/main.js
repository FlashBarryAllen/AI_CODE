// 简单的JavaScript功能示例
document.addEventListener('DOMContentLoaded', function() {
    console.log('知识分享网站已加载');
    
    // 添加平滑滚动效果到锚点链接
    const links = document.querySelectorAll('nav a[href^="#"]');
    links.forEach(link => {
        link.addEventListener('click', function(e) {
            e.preventDefault();
            
            const targetId = this.getAttribute('href');
            const targetSection = document.querySelector(targetId);
            
            if (targetSection) {
                window.scrollTo({
                    top: targetSection.offsetTop - 70,
                    behavior: 'smooth'
                });
            }
        });
    });
});