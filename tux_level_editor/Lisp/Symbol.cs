//  $Id: Symbol.cs 4667 2007-01-23 18:19:14Z anmaster $
namespace Lisp {

public sealed class Symbol {
	private string name;
	public string Name {
		get {
			return name;
		}
	}

	public Symbol(string Name) {
		this.name = Name;
	}

	public override string ToString() {
		return "`" + name + "`";
	}
}

}
