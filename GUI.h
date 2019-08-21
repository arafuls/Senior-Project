#pragma once


namespace gui
{
	class Button
	{
	private:
		enum BTN_STATUS { INACTIVE = 0, HOVER, ACTIVE };
		unsigned int m_buttonStatus;
		unsigned int m_identifier;

		sf::RectangleShape m_button;
		sf::Font* m_font;
		sf::Text m_text;

		sf::Color m_textInactiveColor;
		sf::Color m_textHoverColor;
		sf::Color m_textActiveColor;

		sf::Color m_inactiveColor;
		sf::Color m_hoverColor;
		sf::Color m_activeColor;

		sf::Color m_outlineInactiveColor;
		sf::Color m_outlineHoverColor;
		sf::Color m_outlineActiveColor;


	public:
		Button(
			float a_x, float a_y, int a_w, int a_h,
			sf::Font * a_font, unsigned int a_charSize, std::string a_text,
			sf::Color a_textInactiveColor, sf::Color a_textHoverColor, sf::Color a_textActiveColor,
			sf::Color a_inactiveColor, sf::Color a_hoverColor, sf::Color a_activeColor,
			sf::Color a_outlineInactiveColor = sf::Color::Transparent, 
			sf::Color a_outlineHoverColor = sf::Color::Transparent,
			sf::Color a_outlineActiveColor = sf::Color::Transparent,
			unsigned int a_identifier = 0);
		~Button();

		const bool IsPressed() const;

		const unsigned int & GetIdentifier() const;
		void SetIdentifier(const unsigned int a_identifier);

		const std::string GetString();
		void SetString(const std::string a_string);

		void Update(const sf::Vector2f& a_mousePos);
		void Render(sf::RenderTarget & a_target);
	};

	class DropDownList 
	{
	private:
		float m_dropTimer;
		float m_dropTimerCap;

		sf::Font & m_font;
		std::vector<gui::Button*> m_itemList;	// DropDownList Vector
		gui::Button* m_activeItem;				// Current selection
		bool m_display;

	public:
		DropDownList
		(
			float a_x, float a_y,
			int a_width, int a_height,
			std::string a_itemList[], 
			sf::Font & a_font, 
			unsigned int a_idx, 
			unsigned int a_size
		);
		~DropDownList();

		const bool GetDropTimer();
		void UpdateDropTimer(const float & a_dt);

		const unsigned int & GetActiveElementIdentifier() const;

		void Update(const sf::Vector2f & a_mousePos, const float & a_dt);
		void Render(sf::RenderTarget & a_target);

	};
}

