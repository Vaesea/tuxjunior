//  $Id: Util.cs 4507 2006-12-28 14:44:46Z anmaster $
using System;
using System.IO;
using Lisp;
using Resources;

/// <summary>This class contains some convenience functions</summary>
public static class Util {
	public static List Load(string Filename, string RootElement) {
		return Load(ResourceManager.Instance.Get(Filename), Filename, RootElement);
	}

	public static List Load(TextReader Reader, string Source, string RootElement) {
		try {
			Lexer Lexer = new Lexer(Reader);
			Parser Parser = new Parser(Lexer);

			List Root = Parser.Parse();
			Properties RootP = new Properties(Root);

			List Result = null;
			if(!RootP.Get(RootElement, ref Result))
				throw new LispException("'" + Source + "' is not a " + RootElement + " file");

			return Result;
		} catch(Exception e) {
			throw new LispException("Problem parsing '" + Source + "': " + e.Message, e);
		}
	}
}
