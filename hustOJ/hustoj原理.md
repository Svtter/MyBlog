HUSTOJ原理
===

个人认为组成就很好的说明远离了- -。

HUSTOJ判题分为几个部分，判题服务器，web服务器，数据库服务器。

- 判题服务器的作用
    如果判题队列有题目，则访问数据库机提取题目和提交的代码，负责准备运行环境、数据，运行并监控目标程序的系统调用（防止出现直接访问OJ等的作弊行为），判断运行结果并且写入数据库。 
- 数据库服务器作用
    存储导入的题目，以及从web端口或者http发送的代码，为判题机提供数据，为web服务器提供题目的数据库支持。
- web服务器的作用
    接受代码的提交，存入数据库，并且加入判题队列。提取数据库中的原题目。

总体流程可为如此：


```seq
Title: 判题过程
web服务器->数据库服务器: 提交题目，加入判题队列
数据库服务器-->判题服务器[1~n]: 判断判题队列
数据库服务器->判题服务器[1~n]: 获取题目，代码
判题服务器[1~n]->数据库服务器: 返回结果并且写入
数据库服务器-->web服务器: 获取判题结果
```


<div class="md-section-divider"></div>

<div class="md-section-divider"></div>

<h1 id="hustoj的运作方式">HUSTOJ的运作方式</h1>

<div class="md-section-divider"></div>

<h2 id="hustoj实现">HUSTOJ实现</h2>

<ul>
<li>两大部分，<strong>core</strong>和<strong>web</strong>，分别对应判题和数据管理。</li>
<li>两大功能两者之间的数据交换有两种方式： <br>
<ol><li>通过MySQL数据库进行轮询。</li>
<li>通过wget<a href="#fn:wget" id="fnref:wget" title="查看注脚" class="footnote">[1]</a>实现的http请求。</li></ol></li>
</ul>

<p>两种方式的选择在判题端的配置文件<code>/home/judge/etc/judge.conf</code>中.<code>HTTP_JUDGE=1</code>启用前者，不为1启用后者。</p>

<p><br></p>

<ul>
<li><p>core分为3部分，<strong>judged, jduge_client,sim<a href="#fn:sim" id="fnref:sim" title="查看注脚" class="footnote">[2]</a></strong></p>

<ul><li>judged为服务进程，负责轮询数据库或者web端，提取判题队列 <br>
<ul><li>如果在判题队列中出现题目，则启动judge_client判题</li></ul></li>
<li>judge_client为实际的判题程序，负责准备运行环境，数据，运行并监控目标程序的系统调用，采集运行指标，判断运行结果。</li>
<li>judge_client通过调用<strong>sim</strong>检查是否抄袭，判定结果的相似性，并写回数据库与web端。 <br>
<br></li></ul></li>
</ul>

<div class="md-section-divider"></div>

<h2 id="hustoj原理">HUSTOJ原理</h2>

<p>个人认为组成就很好的说明远离了- -。</p>

<p>HUSTOJ判题分为几个部分，判题服务器，web服务器，数据库服务器。</p>

<ul>
<li>判题服务器的作用 <br>
如果判题队列有题目，则访问数据库机提取题目和提交的代码，负责准备运行环境、数据，运行并监控目标程序的系统调用（防止出现直接访问OJ等的作弊行为），判断运行结果并且写入数据库。 </li>
<li>数据库服务器作用 <br>
存储导入的题目，以及从web端口或者http发送的代码，为判题机提供数据，为web服务器提供题目的数据库支持。</li>
<li>web服务器的作用 <br>
接受代码的提交，存入数据库，并且加入判题队列。提取数据库中的原题目。</li>
</ul>

<p>总体流程可为如此：</p>

<div class="md-section-divider"></div>

<div class="sequence-diagram theme theme-white"><svg style="overflow: hidden; position: relative;" xmlns="http://www.w3.org/2000/svg" width="523" version="1.1" height="386"><desc>Created with Raphaël 2.1.2</desc><defs><path id="raphael-marker-block" d="M5,0 0,2.5 5,5z" stroke-linecap="round"></path><marker refY="2.5" refX="2.5" orient="auto" markerWidth="5" markerHeight="5" id="raphael-marker-endblock55"><use stroke="none" fill="#000" stroke-width="1.0000" transform="rotate(180 2.5 2.5) scale(1,1)" xlink:href="#raphael-marker-block"></use></marker></defs><rect stroke-width="2" style="" stroke="#000000" fill="none" ry="0" rx="0" r="0" height="32" width="74" y="10" x="10"></rect><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="64" y="15" x="15"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="26" x="47" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">判题过程</tspan></text><rect stroke-width="2" style="" stroke="#000000" fill="none" ry="0" rx="0" r="0" height="42" width="98" y="52" x="10"></rect><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="78" y="62" x="20"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="73" x="59" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">web服务器</tspan></text><rect stroke-width="2" style="" stroke="#000000" fill="none" ry="0" rx="0" r="0" height="42" width="98" y="324" x="10"></rect><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="78" y="334" x="20"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="345" x="59" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">web服务器</tspan></text><path stroke-width="2" d="M59,94L59,324" stroke="#000000" fill="none" style=""></path><rect stroke-width="2" style="" stroke="#000000" fill="none" ry="0" rx="0" r="0" height="42" width="116" y="52" x="197"></rect><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="96" y="62" x="207"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="73" x="255" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">数据库服务器</tspan></text><rect stroke-width="2" style="" stroke="#000000" fill="none" ry="0" rx="0" r="0" height="42" width="116" y="324" x="197"></rect><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="96" y="334" x="207"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="345" x="255" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">数据库服务器</tspan></text><path stroke-width="2" d="M255,94L255,324" stroke="#000000" fill="none" style=""></path><rect stroke-width="2" style="" stroke="#000000" fill="none" ry="0" rx="0" r="0" height="42" width="160" y="52" x="333"></rect><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="140" y="62" x="343"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="73" x="413" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">判题服务器[1~Tn]</tspan></text><rect stroke-width="2" style="" stroke="#000000" fill="none" ry="0" rx="0" r="0" height="42" width="160" y="324" x="333"></rect><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="140" y="334" x="343"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="345" x="413" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">判题服务器[1~Tn]</tspan></text><path stroke-width="2" d="M413,94L413,324" stroke="#000000" fill="none" style=""></path><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="176" y="108" x="69"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="119" x="157" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">提交题目，加入判题队列</tspan></text><path stroke-dasharray="0" marker-end="url(#raphael-marker-endblock55)" stroke-width="2" d="M59,136C59,136,219.45269107818604,136,250.00764689873904,136" stroke="#000000" fill="none" style=""></path><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="96" y="150" x="286"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="161" x="334" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">判断判题队列</tspan></text><path stroke-dasharray="6,2" marker-end="url(#raphael-marker-endblock55)" stroke-width="2" d="M255,178C255,178,381.11905094981194,178,407.99940531484754,178" stroke="#000000" fill="none" style=""></path><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="112" y="192" x="278"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="203" x="334" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">获取题目，代码</tspan></text><path stroke-dasharray="0" marker-end="url(#raphael-marker-endblock55)" stroke-width="2" d="M255,220C255,220,381.11905094981194,220,407.99940531484754,220" stroke="#000000" fill="none" style=""></path><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="128" y="234" x="270"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="245" x="334" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">返回结果并且写入</tspan></text><path stroke-dasharray="0" marker-end="url(#raphael-marker-endblock55)" stroke-width="2" d="M413,262C413,262,286.88094905018806,262,260.00059468515246,262" stroke="#000000" fill="none" style=""></path><rect style="" stroke="none" fill="#ffffff" ry="0" rx="0" r="0" height="22" width="96" y="276" x="109"></rect><text font-family="Andale Mono, monospace" font-size="16px" fill="#000000" stroke="none" font="10px &quot;Arial&quot;" text-anchor="middle" y="287" x="157" style="text-anchor: middle; font: 16px Andale Mono,monospace;"><tspan dy="6">获取判题结果</tspan></text><path stroke-dasharray="6,2" marker-end="url(#raphael-marker-endblock55)" stroke-width="2" d="M255,304C255,304,94.54730892181396,304,63.99235310126096,304" stroke="#000000" fill="none" style=""></path></svg></div>

<div class="footnotes">
<hr>
<small>

<span id="fn:wget">[1] </span>wget是Linux下的一个开源http客户端，提供了基于命令行的http交互功能。 <a href="#fnref:wget" title="回到文稿" class="reversefootnote">↩</a><br>

<span id="fn:sim">[2] </span>sim为第三方应用程序，可进行语法分析判断文本相似度，通过检验程序将由judge_client复制进题目数据的AC目录，成为新的参考样本。 <a href="#fnref:sim" title="回到文稿" class="reversefootnote">↩</a><br>

</small>
</div>
