//  $Id: ICustomLispSerializer.cs 5540 2008-06-09 00:52:49Z sik0fewl $
using Lisp;

namespace Lisp
{
	/// <summary>
	///		Implement this interface to handle the seralizing
	///		on your own when seralizing the class.
	/// </summary>
	/// <seealso cref="ILispSerializer"/>
	public interface ICustomLispSerializer {
		/// <summary>
		///		Should populate the object from <paramref name="Props"/>
		/// </summary>
		/// <param name="Props">The serialized data.</param>
		/// <seealso cref="CustomLispWrite"/>
		void CustomLispRead(Properties Props);
		/// <summary>
		///		Should serialize the object to <paramref name="Writer"/>
		/// </summary>
		/// <param name="Writer">a <see cref="Lisp.Writer"/> to serialize to.</param>
		/// <seealso cref="CustomLispRead"/>
		void CustomLispWrite(Writer Writer);
		/// <summary>
		/// Called after <see cref="CustomLispRead"/>.
		/// </summary>
		/// <remarks>
		///		There are no examples what this should be used for (all are empty
		///		in the classes that implement this interface) but it is always
		///		called after <see cref="CustomLispRead"/> by the
		///		<see cref="LispReader.LispRootSerializer"/>.
		/// </remarks>
		/// <seealso cref="CustomLispRead"/>
		void FinishRead();
	}

	/// <summary>
	///		Implement this interface to handle the serializing of some other
	///		class or struct in a special way.
	/// </summary>
	/// <seealso cref="ICustomLispSerializer"/>
	/// <seealso cref="LispReader.LispCustomSerializerAttribute"/>
	public interface ILispSerializer {
		/// <summary>
		///		Creates an instance from the serialized object in
		///		<paramref name="list"/>
		/// </summary>
		/// <param name="list">The serialized object</param>
		/// <returns>The unserialized object</returns>
		/// <seealso cref="Write"/>
		object Read(List list);
		/// <summary>
		///		Seralizes <paramref name="Object"/> using <paramref name="writer"/>
		/// </summary>
		/// <param name="writer">
		///		A <see cref="Writer"/> that <paramref name="Object"/> should be
		///		seralized to.</param>
		/// <param name="name">
		///		Name that should be used for the serialized lisp tree.
		/// </param>
		/// <param name="Object">
		///		The object to write.
		/// </param>
		/// <seealso cref="Read"/>
		void Write(Writer writer, string name, object Object);
	}

}
