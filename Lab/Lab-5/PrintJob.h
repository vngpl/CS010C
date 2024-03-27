#pragma once

class PrintJob {
	private:
		int priority;
		int jobNumber;
		int numPages;

	public:
		PrintJob (int, int, int);
		// ~PrintJob();
		// PrintJob(const PrintJob&) = delete;
		// PrintJob& operator=(const PrintJob&) = delete;
		int getPriority();
		int getJobNumber();
		int getPages();
};
