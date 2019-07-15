<?php
$name = @$_SERVER['QUERY_STRING'] or $name = '';

$xml = new DOMDocument();
$xml->load("$name.xml");

$xsl = new DOMDocument();
$xsl->load('documentation.xsl');

$proc = new XSLTProcessor;
$proc->importStyleSheet($xsl);
echo $proc->transformToXML($xml);
?>