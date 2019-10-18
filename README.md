---
permalink: /
sidebar: toc
toc_icon: "cog"
toc_label: "My Table of Contents"
---

<ul>
    {% for item in site.data.samplelist[page.sidebar] %}
      <li><a href="{{ item.url }}">{{ item.title }}</a></li>
    {% endfor %}
</ul>

# legato_info
A place to document stuff specific to the use of Legato and it's target systems

[FX30 WP77xx](FX30WP77)  
[FX30 WP8548](FX30WP85)


# Images location

[binary](https://www.dropbox.com/home/LegatoYoctoBinaryImages)

