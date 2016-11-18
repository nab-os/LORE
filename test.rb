require 'github/markup'

def main()

	file = "README.md"

	GitHub::Markup.render(file, File.read(file))

end
