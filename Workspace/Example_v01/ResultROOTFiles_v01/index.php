<html>
<head>
<title><?php echo getcwd(); ?></title>
<style type='text/css'>
   div.pic { 
   display: block;
   float: left;
   border: 1px solid gray;
   margin: 3px;
 }
</style>
</head>
<body>
<!-- HERE COMMENTED REGION BEGINS... 
<h1><?php echo getcwd(); ?></h1>
... HERE COMMENTED REGION ENDS -->
<h2><a name="plots">Plots</a></h2>
<!-- HERE COMMENTED REGION BEGINS... 
<p><form>Filter: <input type="text" name="match" size="30" value="<?php if (isset($_GET['match'])) print htmlspecialchars($_GET['match']);  ?>" /><input type="Submit" value="Go" /></form></p>
... HERE COMMENTED REGION ENDS -->
<div>
<?php
$remainder = array();
if ($_GET['noplots']) {
  print "Plots will not be displayed.\n";
} else {
  //$other_exts = array('.pdf', '.cxx', '.eps');
  foreach (glob("*") as $filename) {
    if (!preg_match('/.*\.png$/', $filename) && !preg_match('/.*\.gif.*$/', $filename)) {
      if (!preg_match('/.*\.php.*$/', $filename)) {
	array_push($remainder, $filename);
      }
      continue;
    }
    if (isset($_GET['match']) && !fnmatch('*'.$_GET['match'].'*', $filename)) continue;
    print "<div class='pic'>\n";
    print "<h3><a href=\"$filename\">$filename</a></h3>";
    print "<a href=\"$filename\"><img src=\"$filename\" style=\"border: none; width: 300px; \"></a>";
    //$others = array();
    //foreach ($other_exts as $ex) {
    //    if (file_exists(str_replace('.png', $ex, $filename))) {
    //        array_push($others, "<a class=\"file\" href=\"".str_replace('.png', $ex, $filename)."\">[" . $ex . "]</a>");
    //    }
    //}
    //if ($others) print "<p>Also as ".implode(', ',$others)."</p>";
    print "</div>";
  }
 }
?>
</div>
<div style="display: block; clear:both;">
  <h2><a name="files">&nbsp;<P>Files</a></h2>
<ul>
<?
foreach ($remainder as $filename) {
  print "<li><a href=\"$filename\">$filename</a></li>";
}
?>
</ul>
</div>
</body>
</html>
