% This updated version was modified for the 2017 standards set by the Graduate School of Arts and Sciences at Dartmouth College by David Freund and Daryl DeFord. The changes from the previous version include new formatting for chapters, sections, subsections, and subsubsections.

%%
%% This is file `dcthesis.cls',
%% generated with the docstrip utility.
%%
%% The original source files were:
%%
%% dcthesis.dtx  (with options: `source')
%% 
%%
%% This file is part of the dcLaTeX project.
%%
%% Copyright (C) 2007 by F. G. Dorais.
%%
%% This work may be distributed and/or modified under the conditions
%% of the LaTeX Project Public License, either version 1.3 of this
%% license or (at your option) any later version.  The latest version
%% of this license is in
%%
%%     http://www.latex-project.org/lppl.txt
%%
%% and version 1.3 or later is part of all distributions of LaTeX
%% version 2005/12/01 or later.
%%
%% $Id: dcthesis.dtx,v 1.4 2007-08-12 08:06:53 dorais Exp $
\NeedsTeXFormat{LaTeX2e}[1999/12/01]
\ProvidesClass{dcthesis}
    [2007/06/22 v1.0 dcLaTeX Thesis Class]
\newif\if@mainmatter \@mainmattertrue
\newif\if@copyright \@copyrightfalse
\newif\if@noheadings \@noheadingsfalse
%Make copyright option
\DeclareOption{copyright}{
  \@copyrighttrue
  \newcommand{\copyrightname}{\@author}
  \newcommand{\copyrightyear}{\the\year}
}
\newif\if@final \@finaltrue
\DeclareOption{final}{
  \@finaltrue
  \PassOptionsToClass{final}{book}
}

\DeclareOption{noheadings}{
  \@noheadingstrue
}

%Set properties of various options
\DeclareOption{draft}{
  \@finalfalse
  \PassOptionsToClass{draft}{book}
}

\DeclareOption{singlespacing}{
  \AtBeginDocument{%
    \if@final%
      \ClassWarningNoLine{dcthesis}%
          {Option singlespacing ignored in final mode}%
      \doublespacing%
    \else%
      \singlespacing%
    \fi%
  }
}
\DeclareOption{onehalfspacing}{
  \AtBeginDocument{%
    \if@final%
      \ClassWarningNoLine{dcthesis}%
          {Option onehalfspacing ignored in final mode}%
      \doublespacing%
    \else%
      \onehalfspacing%
    \fi%
  }
}
\DeclareOption{doublespacing}{\AtBeginDocument{\doublespacing}}
\DeclareOption{twoside}{\OptionNotUsed}
\DeclareOption{notitlepage}{\OptionNotUsed}
\DeclareOption{twocolumn}{\OptionNotUsed}
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{book}}
\ExecuteOptions{final,doublespacing,oneside}
\ProcessOptions

%Load the necissary classes and packages
\if@final\LoadClass[titlepage,onecolumn,letterpaper,12pt,oneside]{book}
\else\LoadClass[titlepage,onecolumn,letterpaper,12pt]{book}\fi

\RequirePackage[doublespacing]{setspace}
\RequirePackage{fancyhdr}
\RequirePackage{titlesec}

%Utilities stuff for maketitle
\def\@school{Dartmouth College}
\def\@location{Hanover, New Hampshire}
\newcommand*{\committee}[5][]{%
  \ifx#1\@empty\else\def\@dean{#1}\fi%
  \def\@advisor{#2}%
  \def\@examinera{#3}%
  \def\@examinerb{#4}%
  \def\@examinerc{#5}%
}
\newcommand*{\degree}[1]{\def\@degree{#1}}
\newcommand*{\field}[1]{\def\@field{#1}}
\newcommand*{\school}[2]{\def\@school{#1}\def\@location{#2}}
\renewenvironment{titlepage}{\newpage}{\newpage}
\newcommand{\@signatureline}[1]{%
  \begin{minipage}{2.66667in}%
    \begin{singlespace}
      \vspace{.3in}
      \underline{\hspace{2.6667in}} \par #1 %
    \end{singlespace}
   \end{minipage}%
}
\newcommand{\@longsignatureline}[1]{%Required for the Dean's title to fit.
  \begin{minipage}{3in}%
    \begin{singlespace}
      \vspace{.3in}
      \underline{\hspace{2.6667in}} \par #1 %
    \end{singlespace}
   \end{minipage}%
}

%Command to make the title page
%Salient features are the fact that this is page 0, to take into
%account the unnumbered copyrights page and the use of the committee
%command from above
\renewcommand{\maketitle}{
  \setcounter{page}{0}
  \begin{titlepage}
    \thispagestyle{empty}
    \begin{doublespace}
      \begin{center}
        {\bfseries \MakeUppercase{\@title} \par}
        A Thesis \par
        Submitted to the Faculty \par
        in partial fulfillment of the requirements for the \par
        degree of \par
        \@degree \par
        in \par
        \@field \par
        by \par
        \@author \par
        \MakeUppercase{\@school} \par
        \@location \par
        \@date \par
        \vfill
        \begin{tabular}[t]{cc}
          & Examining Committee: \\
          & \@signatureline{\@advisor, Chair} \\
          & \@signatureline{\@examinera} \\
          & \@signatureline{\@examinerb} \\
          & \@signatureline{\@examinerc} \\
          \@longsignatureline{\@dean \par Dean of Graduate and Advanced Studies}
        \end{tabular}
      \end{center}
    \end{doublespace}
    \newpage
    \thispagestyle{empty}
    \if@copyright
      \begin{singlespace}
        \begin{center}
          Copyright by \par
          \copyrightname \par
          \copyrightyear
        \end{center}
      \end{singlespace}
    \fi
    \null\vfil
  \end{titlepage}

% Code for creating empty pages, since we have skipped a page this 
% has been modified to only start the preliminary sections on even
% numbered pages

\makeatletter
\def\cleardoublepage{\clearpage\if@twoside \ifodd\c@page%
    \hbox{}
    \thispagestyle{empty}
    \newpage
    \if@twocolumn\hbox{}\newpage\fi\fi\fi}
\makeatother \clearpage{\pagestyle{empty}\cleardoublepage}

}

%Frontend command
%Set the page numbering and header scheme for the frontend. 
\renewcommand\frontmatter{%
  \@mainmatterfalse%
  %Headers and Footers
  \renewcommand\headrulewidth{0pt} 
  \fancyhf{}
  \if@twoside
  \fancyfoot[RE,LO]{\thepage}\else
   \fancyfoot[C]{\thepage}\fi
  \pagenumbering{roman}
}

%Main section command.  Change headers and footers, reset the page
%counter and switch the \cleardoublepage back to odds
\renewcommand\mainmatter{%
  \cleardoublepage
  \@mainmattertrue%
  %Headers and Footers
	\titleformat{\chapter}[display]
		{\normalfont\Large\filcenter}
		{\titlerule[1pt]%
			\vspace{10pt}%
			%\titlerule
			%\vspace{1pc}%
			\sffamily\LARGE \chaptertitlename\ \thechapter} %\MakeUppercase{\chaptertitlename} \thechapter}
		{1pc}
		{\titlerule[1pt]
			\vspace{1pc}%
			\Huge
			\bfseries}
			
	\titleformat{\section}[frame]
		{\normalfont}
		{\filright
		\sffamily
		\large
		\enspace Section \thesection\enspace}
		{8pt}
		{\filcenter\Large\bfseries}		
			
	\titleformat{\subsection}
		{\bfseries}
		{\thesubsection.}
		{.5em}
		{}
		[\titlerule]

	\titleformat{\subsubsection}[runin]
		{\bfseries\itshape}
		{}
		{0pt}
		{}
		[.]

  \if@noheadings\else
  \renewcommand\headrulewidth{.1pt}
  \fancyhead[LO]{\sffamily\sc \rightmark}
  \fancyhead[RE]{\sffamily\sc \leftmark}\fi
  \if@twoside
  \fancyfoot[LE,RO]{\thepage}
  \fancyfoot[LO,RE]{}\else
  \fancyfoot[C]{\thepage}\fi
  \pagenumbering{arabic}%
  %Code for creating empty pages
  \makeatletter
  \def\cleardoublepage{\clearpage\if@twoside \ifodd\c@page\else%
  \hbox{}
  \thispagestyle{empty}
  \newpage
  \if@twocolumn\hbox{}\newpage\fi\fi\fi}
  \makeatother \clearpage{\pagestyle{empty}\cleardoublepage}
}

%Backend command
\renewcommand\backmatter{%
  \cleardoublepage%
  \@mainmatterfalse%  
}

%Page Layout
%\@marginsize is for the lefthand margin
%\@smarginsize is for the other margin
\newlength{\@marginsize}
\newlength{\@smarginsize}
\newlength{\@tmarginsize}
\if@twoside
\setlength{\@smarginsize}{1.25in}
\setlength{\@marginsize}{1.25in}\else
\setlength{\@marginsize}{1.5in}
\setlength{\@smarginsize}{1in}\fi
\setlength{\@tmarginsize}{1in}
\if@noheadings
\setlength{\headheight}{0pt}
\setlength{\headsep}{0in}\else
\setlength{\headheight}{16pt}
\setlength{\headsep}{.25in}\fi
\setlength{\textwidth}{\paperwidth}
\addtolength{\textwidth}{-\@marginsize}
\addtolength{\textwidth}{-\@smarginsize}
\setlength{\oddsidemargin}{\@marginsize}
\addtolength{\oddsidemargin}{-1in}
\setlength{\evensidemargin}{\oddsidemargin}
\setlength{\textheight}{\paperheight}
\addtolength{\textheight}{-\headheight}
\addtolength{\textheight}{-\headsep}
\addtolength{\textheight}{-\footskip}
\addtolength{\textheight}{-\@tmarginsize}
\addtolength{\textheight}{-\@tmarginsize}
\setlength{\topmargin}{\@tmarginsize}
\addtolength{\topmargin}{-1in}
\pagestyle{fancy}

%%Some Defaults
%\committee[F. Jon Kull, Ph.D.]{}{}{}{}
%\school{Dartmouth College}{Hanover, New Hampshire}
%\degree{Doctor of Philosophy}
%\field{Mathematics}
\endinput