<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output indent="yes" method="xml" media-type="text/xhtml"
		omit-xml-declaration="yes" />

	<xsl:strip-space elements="*" />
	
	<xsl:template name="contents">
		<li>
			<a href="#{translate(@title, ' ', '_')}">
				<xsl:value-of select="@title" />
			</a>
			<xsl:if test="child::section">
				<ol>
					<xsl:for-each select="child::section">
						<xsl:call-template name="contents" />
					</xsl:for-each>
				</ol>
			</xsl:if>
		</li>
	</xsl:template>
	<xsl:template name="doc-section">
		<xsl:param name="heading-level" />

		<div id="{translate(@title, ' ', '_')}" class="section section-level-{$heading-level}">
			<xsl:element name="h{$heading-level}">
				<xsl:attribute name="class">heading</xsl:attribute>
				<xsl:value-of select="@title" />
			</xsl:element>
			<xsl:for-each select="child::*">
				<xsl:choose>
					<xsl:when test="name() = 'section'">
						<xsl:call-template name="doc-section">
							<xsl:with-param name="heading-level" select="$heading-level + 1" />
						</xsl:call-template>
					</xsl:when>
					<xsl:otherwise>
						<xsl:apply-templates />
					</xsl:otherwise>
				</xsl:choose>
			</xsl:for-each>
		</div>
	</xsl:template>

	<xsl:template match="content">
		<p>
			<xsl:apply-templates select="child::node()" />
		</p>
	</xsl:template>

	<xsl:template match="link">
		<xsl:variable name="maxlength" select="25" />
		<xsl:variable name="protocol-stripped">
			<xsl:choose>
				<xsl:when test="substring-after(text(),'//')">
					<xsl:value-of select="substring-after(normalize-space(),'//')" />
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="normalize-space()" />
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		<xsl:variable name="end"
			select="substring-after(substring-after($protocol-stripped, '.'), '/')" />
		<xsl:variable name="start"
			select="substring-before($protocol-stripped, $end)" />
		<xsl:variable name="text">
			<span class="root">
				<xsl:value-of select="$start" />
			</span>
			<xsl:choose>
				<xsl:when test="string-length($end) &gt; $maxlength">
					<xsl:text>...</xsl:text>
					<xsl:value-of select="substring($end,string-length($end)-$maxlength)" />
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="$end" />
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		<a href="{normalize-space()}">
			<xsl:value-of select="$text" />
		</a>
	</xsl:template>

	<xsl:template match="math">
		<img class="math"
			src="http://latex.codecogs.com/gif.latex?{translate(normalize-space(), ' ', '')}" />
	</xsl:template>

	<xsl:template match="code">
		<xsl:choose>
			<xsl:when test="@src">
					<iframe class="code"
					src="get_code.php?class={@src}&amp;pretty=true&amp;project={(ancestor::*/@linked-project)[last()]}">
					<xsl:text> </xsl:text></iframe>
			</xsl:when>
			<xsl:otherwise>
				<code>
					<xsl:value-of select="text()" />
				</code>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="/section">
		<html>
			<head>
				<title>
					<xsl:value-of select="@title" />
				</title>
				<link rel="stylesheet" type="text/css" href="doc.css" />
			</head>
			<body>
				<div id="main">
					<xsl:call-template name="doc-section">
						<xsl:with-param name="heading-level" select="1" />
					</xsl:call-template>
					<div id="contents">
						<ol>
							<xsl:call-template name="contents" />
						</ol>
					</div>
				</div>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>