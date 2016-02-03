//  $Id: Timer.cs 4507 2006-12-28 14:44:46Z anmaster $
using Sdl;

public static class Timer {
	private static float Time = 0;

	public static float CurrentTime {
		get {
			return Time;
		}
	}

	public static void Update(float ElapsedTime) {
		Time += ElapsedTime;
	}
}
