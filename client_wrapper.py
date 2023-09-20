import pexpect

PROMPT = "> "

class MockClientWrapper:
    def __init__(self):
        # Start the CLI program as a child process using pexpect
        self.proc = pexpect.spawn("./mock_terminal_client")  # Adjust the path if needed
        self.proc.expect(PROMPT)
        return

    def send_command(self, command):
        if command == "exit":
            self.exit()
        # Send a command to the CLI program and return the output
        self.proc.sendline(command)
        self.proc.expect(PROMPT) # we expect the command to finish, and get the prompt back [in a terminal session]
        output: bytes = self.proc.before
        output_decoded: str = output.decode()
        output_lines = output_decoded.splitlines()
        output_lines.pop(0) # first line is the command that was sent
        return output_lines

    def help(self):
        return self.send_command("help")

    def hello(self):
        return self.send_command("hello")
    
    def print(self):
        return self.send_command("print")

    def exit(self):
        # exit does not use send_command, as we don't expect the prompt to return to us
        self.proc.sendline("exit")
        self.proc.expect(pexpect.EOF)
        self.proc.close()

if __name__ == "__main__":
    client = MockClientWrapper()

    print("calling help")
    client_output = client.help()
    print(client_output)

    print("calling hello")
    client_output = client.hello()
    print(client_output)

    print("calling print")
    client_output = client.print()
    print(client_output)

    client.exit()  # Optional, to exit the CLI program gracefully
