TESTLIB_PATH=$(realpath "$(dirname "${BASH_SOURCE[0]}")")

GERROR=0
TERROR=0
RESPONDOK=1

function printFail () {
    TERROR=1
    GERROR=1
    NIZ=${1:-Napaka}
    echo "<span style='color:#AF0000;'>$NIZ</span>"
}
function printOk () {
    NIZ=${1:-"&#x1f5f8"}
    echo "<span style='color:#00AF00;'>$NIZ</span>"
}
function printWarning () {
    NIZ=${1:-"Opozorilo"}
    echo "<span style='color:#AFAF00;'>$NIZ</span>"
}

function printHeader(){
    echo "<DIV CLASS='report'><TABLE WIDTH=100% BORDER=0><TR><TD CLASS='title' COLSPAN=2>$1</TD></TR>"
    echo "<TR><TD CLASS='body'>"
}

function printFooter() {
    echo "</TD>"
    if [ $TERROR -eq 0 ] ; then
        if [ "$RESPONDOK" -eq 0 ] ; then
            CLASS="result"
            TEXT="&nbsp;"
        else
            CLASS="result_ok"
            TEXT="OK"
        fi
    else
        if [ $TERROR -eq 2 ] ; then
            CLASS="result_warning"
            TEXT="Opozorilo"
        else
            CLASS="result_error"
            TEXT="Napaka"
        fi
    fi
    echo "<TD width=1% class='$CLASS'>$TEXT</TD>"
    echo "</TR></TABLE></DIV>"
}

## html header
cat << htmlend
<!DOCTYPE HTML>
<html>
<head>
<style>

/* PrismJS 1.19.0
https://prismjs.com/download.html#themes=prism-okaidia&languages=markup+css+clike+javascript */
/**
 * okaidia theme for JavaScript, CSS and HTML
 * Loosely based on Monokai textmate theme by http://www.monokai.nl/
 * @author ocodia
 */

code[class*="language-"],
pre[class*="language-"] {
	color: #f8f8f2;
	background: none;
	text-shadow: 0 1px rgba(0, 0, 0, 0.3);
	font-family: Consolas, Monaco, 'Andale Mono', 'Ubuntu Mono', monospace;
	font-size: 1em;
	text-align: left;
	white-space: pre;
	word-spacing: normal;
	word-break: normal;
	word-wrap: normal;
	line-height: 1;

	-moz-tab-size: 4;
	-o-tab-size: 4;
	tab-size: 4;

	-webkit-hyphens: none;
	-moz-hyphens: none;
	-ms-hyphens: none;
	hyphens: none;
}

/* Code blocks */
pre[class*="language-"] {
	padding: 1em;
	margin: .5em 0;
	overflow: auto;
	border-radius: 0.3em;
}

:not(pre) > code[class*="language-"],
pre[class*="language-"] {
	background: #272822;
}

/* Inline code */
:not(pre) > code[class*="language-"] {
	padding: .1em;
	border-radius: .3em;
	white-space: normal;
}

.token.comment,
.token.prolog,
.token.doctype,
.token.cdata {
	color: slategray;
}

.token.punctuation {
	color: #f8f8f2;
}

.token.namespace {
	opacity: .7;
}

.token.property,
.token.tag,
.token.constant,
.token.symbol,
.token.deleted {
	color: #f92672;
}

.token.boolean,
.token.number {
	color: #ae81ff;
}

.token.selector,
.token.attr-name,
.token.string,
.token.char,
.token.builtin,
.token.inserted {
	color: #a6e22e;
}

.token.operator,
.token.entity,
.token.url,
.language-css .token.string,
.style .token.string,
.token.variable {
	color: #f8f8f2;
}

.token.atrule,
.token.attr-value,
.token.function,
.token.class-name {
	color: #e6db74;
}

.token.keyword {
	color: #66d9ef;
}

.token.regex,
.token.important {
	color: #fd971f;
}

.token.important,
.token.bold {
	font-weight: bold;
}
.token.italic {
	font-style: italic;
}

.token.entity {
	cursor: help;
}

:root {
  --bodyBackground: #eaeaea url('data:image/jpg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/2wBDAAUDBAQEAwUEBAQFBQUGBwwIBwcHBw8LCwkMEQ8SEhEPERETFhwXExQaFRERGCEYGh0dHx8fExciJCIeJBweHx7/2wBDAQUFBQcGBw4ICA4eFBEUHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh4eHh7/wgARCAAoACgDAREAAhEBAxEB/8QAFwABAQEBAAAAAAAAAAAAAAAAAQACCP/EABUBAQEAAAAAAAAAAAAAAAAAAAAC/9oADAMBAAIQAxAAAADpiaAETIkRERAICIEAgJH/xAAdEAACAgIDAQAAAAAAAAAAAAAAAREhEDFBUWEC/9oACAEBAAE/AFY9Nir5SJ9gR0JVAqTK50eaZ50s3ApIzNxso4SWFEU9D1DYqvR//8QAFhEAAwAAAAAAAAAAAAAAAAAAAAFA/9oACAECAQE/AKEf/8QAFBEBAAAAAAAAAAAAAAAAAAAAQP/aAAgBAwEBPwBP/9k=') repeat scroll top left;
  --borderColor: rgb(77,93,109);
  --backgroundTitleColor:#306384;
  --backgroundSubTitleColor:#b1c2ec;
  --backgroundSubSubTitleColor:#ccd9ff;
  --backgroundSubSubTitleColorDarker:#afb6cc;
  --linkColor:blue;
  --linkHooverColor:red;
  --textColorWhite:white;
  --navbarLinkColor:white;
  --navbarLinkColorHoover:blue;
  --navbarLinkColorHooverBackground:#e3d333;
  --tableRowLightBackground:#f5f5f5;
  --backgroundContentColor:white;
  --backgroundReportErrorColor:#ffafaf;
  --backgroundReportWarningColor:#fffebf;
  --backgroundReportOkColor:#bfffdf;
  --backgroundReportColor:#bfe4ff;
}
body {
  background: var(--bodyBackground);
  font-family: Verdana, Arial, Helvetica, sans-serif;
}

.title {
  font-size:1.2em;  
  font-weight:bold;
  margin:auto;
}

.name {
  font-size:1em;  
  font-weight:normal;
  margin:auto;
}

.grid-container {
  display: grid;
  gap: 5px;
  padding: 0px;
}

a:link {text-decoration: none; color: var(--linkColor);}
a:visited { text-decoration: none; color: var(--linkColor); }
a:hover {text-decoration: underline; color: var(--linkHooverColor);}

#navbar a {
 padding: 0 0.1em;
 display: block;
 text-decoration: none;
}

#navbar a:link {color: var(--navbarLinkColor);}
#navbar a:visited {color: var(--navbarLinkColor);}
#navbar a:hover {color: var(--navbarLinkColorHoover);background:var(--navbarLinkColorHooverBackground);}

.itemTitle {
  grid-area:title;
  text-align: center;
  padding: 5px 5px;
  font-size: 1em;
  border-radius: 2px 2px 10px 10px;
  border-color: var(--borderColor);
  border-style: solid;
  border-width: 1px;
  background-color: var(--backgroundTitleColor);
  color:var(--textColorWhite);
}

.itemNavbar {
  grid-area:navbar;
  text-align: left;
  padding: 5px 5px;
  border-radius: 2px 2px 10px 10px;
  border-color: var(--borderColor);
  border-style: solid;
  border-width: 1px;
  background-color: var(--backgroundTitleColor);
}

.itemContent {
  grid-area:content;
  text-align: left;
  padding: 5px 5px;
  font-size: 1em;
  border-radius: 2px 2px 10px 10px;
  border-color: var(--borderColor);
  border-style: solid;
  border-width: 1px;  
  background-color: white;
}

.itemFooter {
  grid-area:footer;
  text-align: center;
  padding: 0px;
  font-size: 0.5em;
  border-style: none;
}

.itemEmpty {
    grid-area:empty;
    padding: 0px;
    border-style: none;
}

.navbar-container {
    display:flex;
    list-style:none;
    justify-content:space-evenly;    
} 

.navbar-item {
  padding: 3px;
  margin-top: 0px;
  margin-right: 5px;
  font-size:1em;
}

@media (orientation: landscape) {
	.navbar-container {
		flex-flow: column wrap;
	    }
   	.grid-container {
        grid-template-rows: auto min-content 1fr auto;
   	grid-template-columns: 13ch 1fr;
    	grid-template-areas:
    		"title content"
        	"navbar content"
                "empty content"
        	"footer footer";
	}    		
}


@media (orientation: portrait) {
        .navbar-container {
		flex-flow: row wrap;
        }
	.grid-container {
	grid-template-columns: 12ch 1fr;
        grid-template-rows: auto 1fr auto;
    	grid-template-areas:
    		"title navbar"
        	"content content"
        	"footer footer";
	}    
	.navbar-item {
		  font-size: 0.9em;
	}
	.name {
		font-size: 0.9em;
	}
}


.contentTitle {
  text-align: left;
  padding: 5px 5px;
  font-size: 1.2em;
  border-radius: 2px 2px 10px 10px;
  border-color: var(--borderColor);
  border-style: solid;
  border-width: 1px;
  background-color: var(--backgroundTitleColor);
  color:var(--textColorWhite);
}

.textGray {
    color:#707070;
}

.textRed {
    color:red;
}

.vptb {
    padding:15px;    
}

.textGrayStriked {
    color:#707070;
    text-decoration: line-through;
}

.textMessage {
    color:#FF0000;
    font-weight: bold;
}

table.seznam {
    border:0;
    border-collapse:collapse;
}

table.seznam tbody tr:nth-child(odd) {

}

table.seznam tbody tr:nth-child(even) {
    background-color: var(--tableRowLightBackground);
}

.contentVaje {
  text-align: left;
  padding: 5px 5px;
  font-size: 1em;
  background-color: var(--backgroundContentColor);
}

.olTitle {
    font-size:120%;
    font-weight:bold;
}


.content-container {
    display:flex;
    list-style:none;
    flex-direction:column;
} 

.content-item { 
  font-size:1em;
  text-align: left;
  padding: 5px 5px;
  border-radius: 2px 2px 10px 10px;

}

.horscroll {
  overflow-x:scroll;
  white-space: nowrap;
}

table.forum {
    border-collapse: collapse;
    width:100%;
    padding:0;
    
}

.podokno {
    background-color: var(--backgroundSubSubTitleColor);
}

table.nodeTree {
    border-collapse: collapse;    
    width:100%;    
}

table.nodeTree td.levi {
    max-width:min-content;
}

table.nodeTree img{
    border:0;    
}

table.nalogeReport { 
    
    border:1px solid;
    border-color: black;
    border-collapse: collapse;
}

table.nalogeReport td {
    border:1px solid;
    border-color: black;
    background-color: white;    
}

table.nalogeReport td.active {
    background-color: var(--backgroundSubSubTitleColor);
}

table.nalogeReport td.inactive {
    background-color: var(--backgroundSubSubTitleColorDarker);
}

table.nalogeReport td.naslov {
    background-color: var(--backgroundSubTitleColor);
}

td.desno {
    text-align: right;
}

td.sredina {
    text-align:center;
}

td.zgoraj {
    vertical-align: top;
}

span.polovicka {
    font-size:50%;
}

span.vecje {
    font-size:larger;
}

table.nalogeReport a:link{
    text-decoration: none; 
    color: var(--linkColor);
}


table.nalogeReport a:hover {
    text-decoration: underline; 
    color: var(--linkHooverColor);
}



table.nalogeReport img {
    border:0;
}


table.naloga {
    width:100%;
    border:0;
    border-collapse: collapse;
}

.glavniNaslov {
  font-size: 1.2em;
  background-color: var(--backgroundTitleColor);
  color:var(--textColorWhite);
}

.delnaSirina {
    max-width: max-content;
}

.stanje {
  border: 2px solid green;
  border-radius: 10px 10px 10px 10px;
  max-width: max-content;
  background-color: #FFF5EE;
}

.studentChat {
  border: 1px solid;
  border-color: var(--borderColor);
  border-radius: 10px 10px 10px 10px;
  max-width: max-content;
  background-color: var(--backgroundSubSubTitleColor);
  text-align:left;
}

.adminChat {
  border: 1px solid;
  border-color: var(--borderColor);
  border-radius: 10px 10px 10px 10px;
  max-width: max-content;
  background-color: var(--backgroundSubTitleColor);
  text-align:left;
}

.tip0boxcontent_no {
        background-color: #e8f5ff;  
        border-style:solid;
        border-width:thin;
}
.tip1boxcontent_no {
        background-color: #FFFEBF;  
        border-style:solid;
        border-width:thin;
}
.tip2boxcontent_no {
        background-color: #EFFFEF; 
        border-style:solid;
        border-width:thin;
}
.tip3boxcontent_no {
        background-color: #D3BFFF; 
        border-style:solid;
        border-width:thin;
}
.tip4boxcontent_no {
        background-color: #F7F451; 
        border-style:solid;
        border-width:thin;
}
.tip5boxcontent_no {
        background-color: #EFFFEF; 
        border-style:solid;
        border-width:thin;
}
.tip6boxcontent_no {
        background-color: #BFE4FF; 
        border-style:solid;
        border-width:thin;
}
.tip7boxcontent_no {
        background-color: #EFFFEF; 
        border-style:solid;
        border-width:thin;
}
.tip8boxcontent_no {
        background-color: #BFE4FF; 
        border-style:solid;
        border-width:thin;
}
.tip9boxcontent_no {
        background-color: #EFFFEF;  
        border-style:solid;
        border-width:thin;
}


.tip0boxcontent_o {
            background-color: #BFFFDB; 
            border-style:solid;
            border-width:thin;
}
.tip1boxcontent_o {
            background-color: #FFFEBF; 
            border-style:solid;
            border-width:thin;
}
.tip2boxcontent_o {
            background-color: #FFFEBF; 
            border-style:solid;
            border-width:thin;
}
.tip3boxcontent_o {
            background-color: #D3BFFF; 
            border-style:solid;
            border-width:thin;
}
.tip4boxcontent_o {
            background-color: #F7F451; 
            border-style:solid;
            border-width:thin;
}
.tip5boxcontent_o {
            background-color: #FFEFBF; 
            border-style:solid;
            border-width:thin;
}
.tip6boxcontent_o {
            background-color: #BFFFDB; 
            border-style:solid;
            border-width:thin;
}
.tip7boxcontent_o {
            background-color: #FFEFBF; 
            border-style:solid;
            border-width:thin;
}
.tip8boxcontent_o {
            background-color: #BFFFDB; 
            border-style:solid;
            border-width:thin;
}
.tip9boxcontent_o {
            background-color: #FFEFBF; 
            border-style:solid;
            border-width:thin;
}

.tip0boxcontent_t {
            background-color: #FFAFAF; 
            border-style:solid;
            border-width:thin;
}
.tip1boxcontent_t {
            background-color: #FFAFAF;  
            border-style:solid;
            border-width:thin;
}
.tip2boxcontent_t {
            background-color: #FFAFAF; 
            border-style:solid;
            border-width:thin;
}
.tip3boxcontent_t {
            background-color: #FFAFAF; 
            border-style:solid;
            border-width:thin;
}
.tip4boxcontent_t {
            background-color: #FFAFAF;  
            border-style:solid;
            border-width:thin;
}
.tip5boxcontent_t {
            background-color: #FFAFAF; 
            border-style:solid;
            border-width:thin;
}
.tip6boxcontent_t {
            background-color: #FFAFAF; 
            border-style:solid;
            border-width:thin;
}
.tip7boxcontent_t {
            background-color: #FFAFAF; 
            border-style:solid;
            border-width:thin;
}
.tip8boxcontent_t {
            background-color: #FFAFAF;  
            border-style:solid;
            border-width:thin;
}

.tip9boxcontent_t {
            background-color: #FFAFAF;
            border-style:solid;
            border-width:thin;
}

.tip0boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip1boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip2boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip3boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip4boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip5boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip6boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip7boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip8boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}
.tip9boxcontent_nt {
            background-color: #FFDFDF;
            border-style:solid;
            border-width:thin;
}

.generalbox {
    border-radius: 2px 2px 10px 10px;
    padding: 0px;
    margin: 0px;
    margin-bottom: 3px;
    background-color: var(--backgroundContentColor);
}

.error {
    position:       absolute;
    z-index:        130;
    left: 100;
    top: 100;
}

.fullwidth {
    width:100%;
}

a.no:link {text-decoration: none; color:var(--textColorWhite);}
a.no:visited {text-decoration: none; color:var(--textColorWhite);}
a.no:hover {text-decoration: none; color:var(--textColorWhite);}

table.onlinetesttable {
    border: none;
    border-spacing: 0px;
    padding: 5px;
}

table.onlinetesttable th {
    background-color: white;
    text-align: left;
    font-weight: normal;
}

table.onlinetesttable td.checkmark {
    width:1px;
    white-space: nowrap;
}

table.onlinetesttable tbody tr:nth-child(even) {
    background-color: white;
    text-align: left;
}

table.onlinetesttable tbody tr:nth-child(odd) {
    background-color: #f2f2f2;
    text-align: left;
}
table.oprema {
    border:0;
    border-collapse:collapse;
}

table.oprema tbody tr:nth-child(odd) {
    
}

table.oprema tbody tr:nth-child(even) {
    background-color: var(--tableRowLightBackground);
}

table.oprema td {
    padding: 10px;
}
table.oprema th {
    padding: 10px;
}

.bgGrey {
    background-color: #e0e0ff !important;
}

.sporocilo {
  text-align: left;
  padding: 5px 5px;
  font-size: 1em;
  color:black;
  border-radius: 10px 10px 10px 10px;
  border-color: var(--borderColor);
  border-style: solid;
  border-width: 1px;  
  background-color: white;
}

.numberCircle {
    display:inline-block;
    border-radius:25%;
    border:0;
    background: white;
}

pre {
    padding: 1em;
    border: 1px dashed #AFB971;
    color: black;
    background-color: #f9f9f9;
    line-height: 1.1em;
}


.reports_list {
    background-color: white;
}

.report {
    background-color: var(--backgroundReportColor); 
    border-style:solid;
    border-width:thin;

    font-size:1em;
    text-align: left;
    padding: 5px 5px;
    border-radius: 2px 2px 10px 10px;
} 

.report .title {
  grid-area:title;
  text-align: center;
  padding: 5px 5px;
  font-size: 1em;
  border-radius: 2px 2px 10px 10px;
  border-color: var(--borderColor);
  border-style: solid;
  border-width: 1px;
  background-color: var(--backgroundTitleColor);
  color:var(--textColorWhite);
}

.report .result {
    text-align:center;
}

.report .result_ok {
    background-color: var(--backgroundReportOkColor); 
    border-style:solid;
    border-width:thin;
    text-align:center;
}

.report .result_warning {
    background-color: var(--backgroundReportWarningColor); 
    border-style:solid;
    border-width:thin;
    text-align:center;
}

.report .result_error {
    background-color: var(--backgroundReportErrorColor);  
    border-style:solid;
    border-width:thin;
    text-align:center;
}

.report .body {
    grid-area:content;
    text-align: left;
    padding: 5px 5px;
    font-size: 1em;
    border-radius: 2px 2px 10px 10px;
    border-color: var(--borderColor);
    border-style: solid;
    border-width: 1px;
    background-color: white;
}

.report .body .exec_command {
    background-color: var(--backgroundReportColor);
    border-style:solid;
    border-width:thin;
}

.report .body .output {
    
}
.report .body .cmd_output {
    background-color: black;
    color: white;
}

.report_summary {
    background-color: white;
}


pre.cmd_output {
    white-space:pre-wrap;
}

img.iconimage {
    width:16px;
    height:16px;
    font-size: 0.5em;
}

img.wikipic {
    max-width:100%;
    height:100%;
}

.cmd_output {
    background-color: black;
    color: white;
}

pre.cmd_output {
    white-space: pre-wrap;
    line-height: normal;
}


pre.cmd_output .bold {
  font-weight: bold;
}
pre.cmd_output .dim {
  filter: brightness(0.5);
}
pre.cmd_output .italic {
  font-style: italic;
}
pre.cmd_output .underline {
  text-decoration: underline;
}
pre.cmd_output .blink {
  animation: blinker 1s ease infinite;
}
@keyframes blinker {
  50% { opacity: 0; }
}
pre.cmd_output .inverse {
  filter: invert(100%);
}
pre.cmd_output .strikethrough {
  text-decoration: line-through;
}

pre.cmd_output .black {
  color: black;
}
pre.cmd_output .red {
  color: red;
}
pre.cmd_output .green {
  color: green;
}
pre.cmd_output .yellow {
  color: yellow;
}
pre.cmd_output .blue {
  color: blue;
}
pre.cmd_output .magenta {
  color: magenta;
}
pre.cmd_output .cyan {
  color: cyan;
}
pre.cmd_output .white {
  color: white;
}

pre.cmd_output .bg_black {
  background-color: black;
}
pre.cmd_output .bg_red {
  background-color: red;
}
pre.cmd_output .bg_green {
  background-color: green;
}
pre.cmd_output .bg_yellow {
  background-color: yellow;
}
pre.cmd_output .bg_blue {
  background-color: blue;
}
pre.cmd_output .bg_magenta {
  background-color: magenta;
}
pre.cmd_output .bg_cyan {
  background-color: cyan;
}
pre.cmd_output .bg_white {
  background-color: white;
}
pre.cmd_output .hidden {
  color: transparent;
}
</style>
</head>
<body>
<div class='reports_list'>
htmlend

## html footer
function atexitTestlib () {
    echo "<div class='report_summary'>"
    if [ $GERROR -eq 0 ] ; then
        echo "<TABLE BORDER=0><TR><TD></TD><TD><span style='font-size:1.2'>Avtomatski preizkusi niso odkrili napak, kar pa še ni zagotovilo, da napak ni!</span></TD></TR></TABLE>"
    else 
        if [ $GERROR -eq 2 ] ; then 
            echo "<TABLE BORDER=0><TR><TD></TD><TD><span style='font-size:1.2em'>Nekateri avtomatski preizkusi so se končali z opozorilom</span></TD></TR></TABLE>"
        else
            echo "<TABLE BORDER=0><TR><TD></TD><TD><span style='font-size:1.2em'>Nekateri izmed avtomatskih preizkusov niso uspeli</span></TD></TR></TABLE>"
        fi
    fi
    echo "</div></div>"

    echo "</body>"
}

trap atexitTestlib EXIT

