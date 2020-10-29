namespace
{
    constexpr auto tooltipFontSize = 16.0f;
    constexpr auto maxTooltipWidth = 1000000;
}

//==============================================================================
void SharedFonts::initialise()
{
    NEURALDSP_CRASH_TRACER

    Typeface::Ptr typefaceToCheck
   #if USE_ROBOTO
    = roboto.regular.normal;
   #else
    = plex.regular.normal;
   #endif
    if (typefaceToCheck != nullptr)
        return;

    using namespace BinaryData;

   #if ! USE_ROBOTO
    plex.regular.thin       = Typeface::createSystemTypefaceFor (IBMPlexSansThin_ttf, IBMPlexSansThin_ttfSize);
    plex.regular.ultraLight = Typeface::createSystemTypefaceFor (IBMPlexSansExtraLight_ttf, IBMPlexSansExtraLight_ttfSize);
    plex.regular.light      = Typeface::createSystemTypefaceFor (IBMPlexSansLight_ttf, IBMPlexSansLight_ttfSize);
    plex.regular.normal     = Typeface::createSystemTypefaceFor (IBMPlexSansRegular_ttf, IBMPlexSansRegular_ttfSize);
    plex.regular.medium     = Typeface::createSystemTypefaceFor (IBMPlexSansMedium_ttf, IBMPlexSansMedium_ttfSize);
    plex.regular.semiBold   = Typeface::createSystemTypefaceFor (IBMPlexSansBold_ttf, IBMPlexSansBold_ttfSize);
    plex.italic.thin        = Typeface::createSystemTypefaceFor (IBMPlexSansThinItalic_ttf, IBMPlexSansThinItalic_ttfSize);
    plex.italic.ultraLight  = Typeface::createSystemTypefaceFor (IBMPlexSansExtraLightItalic_ttf, IBMPlexSansExtraLightItalic_ttfSize);
    plex.italic.light       = Typeface::createSystemTypefaceFor (IBMPlexSansLightItalic_ttf, IBMPlexSansLightItalic_ttfSize);
    plex.italic.medium      = Typeface::createSystemTypefaceFor (IBMPlexSansMediumItalic_ttf, IBMPlexSansMediumItalic_ttfSize);
    plex.italic.semiBold    = Typeface::createSystemTypefaceFor (IBMPlexSansBoldItalic_ttf, IBMPlexSansBoldItalic_ttfSize);

    //NB: The font doesn't provide an italic version of regular...
   #if 0
    plex.italic.normal = Typeface::createSystemTypefaceFor (IBMPlexSansRegularItalic_ttf, IBMPlexSansRegularItalic_ttfSize);
   #else
    plex.italic.normal = plex.italic.medium;
   #endif
   #else
    roboto.regular.thin         = Typeface::createSystemTypefaceFor (RobotoThin_ttf, RobotoThin_ttfSize);
    roboto.regular.light        = Typeface::createSystemTypefaceFor (RobotoLight_ttf, RobotoLight_ttfSize);
    roboto.regular.normal       = Typeface::createSystemTypefaceFor (RobotoRegular_ttf, RobotoRegular_ttfSize);
    roboto.regular.medium       = Typeface::createSystemTypefaceFor (RobotoMedium_ttf, RobotoMedium_ttfSize);
    roboto.regular.bold         = Typeface::createSystemTypefaceFor (RobotoBold_ttf, RobotoBold_ttfSize);
    roboto.regular.black        = Typeface::createSystemTypefaceFor (RobotoBlack_ttf, RobotoBlack_ttfSize);
    roboto.italic.thin          = Typeface::createSystemTypefaceFor (RobotoThinItalic_ttf, RobotoThinItalic_ttfSize);
    roboto.italic.light         = Typeface::createSystemTypefaceFor (RobotoLightItalic_ttf, RobotoLightItalic_ttfSize);
    roboto.italic.normal        = Typeface::createSystemTypefaceFor (RobotoItalic_ttf, RobotoItalic_ttfSize);
    roboto.italic.medium        = Typeface::createSystemTypefaceFor (RobotoMediumItalic_ttf, RobotoMediumItalic_ttfSize);
    roboto.italic.bold          = Typeface::createSystemTypefaceFor (RobotoBoldItalic_ttf, RobotoBoldItalic_ttfSize);
    roboto.italic.black         = Typeface::createSystemTypefaceFor (RobotoBlackItalic_ttf, RobotoBlackItalic_ttfSize);

    robotoMono.regular.thin     = Typeface::createSystemTypefaceFor (RobotoMonoThin_ttf, RobotoMonoThin_ttfSize);
    robotoMono.regular.light    = Typeface::createSystemTypefaceFor (RobotoMonoLight_ttf, RobotoMonoLight_ttfSize);
    robotoMono.regular.normal   = Typeface::createSystemTypefaceFor (RobotoMonoRegular_ttf, RobotoMonoRegular_ttfSize);
    robotoMono.regular.medium   = Typeface::createSystemTypefaceFor (RobotoMonoMedium_ttf, RobotoMonoMedium_ttfSize);
    robotoMono.regular.bold     = Typeface::createSystemTypefaceFor (RobotoMonoBold_ttf, RobotoMonoBold_ttfSize);
    robotoMono.italic.thin      = Typeface::createSystemTypefaceFor (RobotoMonoThinItalic_ttf, RobotoMonoThinItalic_ttfSize);
    robotoMono.italic.light     = Typeface::createSystemTypefaceFor (RobotoMonoLightItalic_ttf, RobotoMonoLightItalic_ttfSize);
    robotoMono.italic.normal    = Typeface::createSystemTypefaceFor (RobotoMonoItalic_ttf, RobotoMonoItalic_ttfSize);
    robotoMono.italic.medium    = Typeface::createSystemTypefaceFor (RobotoMonoMediumItalic_ttf, RobotoMonoMediumItalic_ttfSize);
    robotoMono.italic.bold      = Typeface::createSystemTypefaceFor (RobotoMonoBoldItalic_ttf, RobotoMonoBoldItalic_ttfSize);
   #endif

    #undef LOAD_TYPEFACE
}

Typeface::Ptr SharedFonts::getTypefaceFromFamily (const Font& source, const String& nameToLookFor,
                                                  Typeface::Ptr regular, Typeface::Ptr bold,
                                                  Typeface::Ptr italic, Typeface::Ptr boldItalic)
{
    if (nameToLookFor.equalsIgnoreCase (source.getTypefaceName()))
    {
        if (source.isBold() && bold != nullptr)
        {
            if (source.isItalic() && italic != nullptr)
                return boldItalic;

            return bold;
        }

        if (source.isItalic() && italic != nullptr)
            return italic;

        jassert (regular != nullptr);
        return regular;
    }

    return {};
}

Typeface::Ptr SharedFonts::getTypefaceFromFamily (const Font& source, const String& nameToLookFor,
                                                  const TypefaceFamily& family)
{
    auto bestBold = family.regular.bold;
    if (bestBold == nullptr)
        bestBold = family.regular.semiBold;

    auto bestBoldItalic = family.italic.bold;
    if (bestBoldItalic == nullptr)
        bestBoldItalic = family.italic.semiBold;

    return getTypefaceFromFamily (source, nameToLookFor,
                                  family.regular.normal, bestBold,
                                  family.italic.normal, bestBoldItalic);
}

//==============================================================================
void SharedResources::initialise()
{
    if (hasInitialised)
        return;

    hasInitialised = true;

    sharedFonts.initialise();
}

//==============================================================================
MainLookAndFeel::MainLookAndFeel()
{
    sharedResources->initialise();

    Font::setDefaultMinimumHorizontalScaleFactor (1.0f);

   #if USE_ROBOTO
    setDefaultSansSerifTypefaceName ("Roboto");
   #else
    setDefaultSansSerifTypefaceName ("Plex");
   #endif

    setColourScheme
    ({
        Colours::white,                 Colours::black,                 Colours::black,
        Colours::black,                 Colours::white,                 GlobalColours::aquaBlueLike,
        GlobalColours::codGrayLight,    GlobalColours::aquaBlueLike,    Colours::white
    });

    setColour (TooltipWindow::backgroundColourId,           Colours::white);
    setColour (TooltipWindow::textColourId,                 Colours::black);
    setColour (TooltipWindow::outlineColourId,              Colours::transparentBlack);
    setColour (CodeEditorComponent::backgroundColourId,     Colours::white);
    setColour (CodeEditorComponent::highlightColourId,      GlobalColours::aquaBlueLike);
    setColour (CodeEditorComponent::defaultTextColourId,    Colours::black);
    setColour (CodeEditorComponent::lineNumberBackgroundId, GlobalColours::codGrayLight);
    setColour (CodeEditorComponent::lineNumberTextId,       Colours::black);
    setColour (ResizableWindow::backgroundColourId,         Colours::black);
    setColour (Toolbar::backgroundColourId,                 Colours::black);
    setColour (HyperlinkButton::textColourId,               Colours::white);
    setColour (DrawableButton::backgroundOnColourId,        GlobalColours::codGrayLight);
    setColour (DrawableButton::backgroundColourId,          Colours::black);
    setColour (TextEditor::backgroundColourId,              Colours::black);
    setColour (TextEditor::textColourId,                    Colours::white);
    setColour (TextEditor::focusedOutlineColourId,          GlobalColours::codGrayLight);
    setColour (TextEditor::outlineColourId,                 GlobalColours::codGrayLight);
}

//==============================================================================
Typeface::Ptr MainLookAndFeel::getTypefaceForFont (const Font& f)
{
    Typeface::Ptr typefaceToUse;
    auto& sharedFonts = sharedResources->sharedFonts;

    if (f.getTypefaceName() == Font::getDefaultSansSerifFontName()
        || f.getTypefaceName() == Font::getDefaultSerifFontName()
        || f.getTypefaceName() == Font::getDefaultMonospacedFontName())
    {
        Font fo (f);
        SharedFonts::TypefaceFamily* family = nullptr;

       #if USE_ROBOTO
        fo.setTypefaceName ("Roboto");
        family = &sharedFonts.roboto;
       #else
        fo.setTypefaceName ("Plex");
        family = &sharedFonts.plex;
       #endif

        typefaceToUse = SharedFonts::getTypefaceFromFamily (fo, fo.getTypefaceName(), *family);
    }

   #if USE_ROBOTO
    if (typefaceToUse == nullptr) typefaceToUse = SharedFonts::getTypefaceFromFamily (f, "Roboto", sharedFonts.roboto);
    if (typefaceToUse == nullptr) typefaceToUse = SharedFonts::getTypefaceFromFamily (f, "RobotoMono", sharedFonts.robotoMono);
   #else
    if (typefaceToUse == nullptr) typefaceToUse = SharedFonts::getTypefaceFromFamily (f, "Plex", sharedFonts.plex);
   #endif

    if (typefaceToUse != nullptr)
        return typefaceToUse;

    return LookAndFeel_V4::getTypefaceForFont (f);
}

//==============================================================================
void MainLookAndFeel::drawTooltip (Graphics& g, const String& text, int width, int height)
{
    if (text.isEmpty())
        return;

    const auto textColour = findColour (TooltipWindow::textColourId);
    jassert (! textColour.isTransparent());
    AttributedString s;
    s.setJustification (Justification::topLeft);
    s.append (text, Font (tooltipFontSize), textColour);

    TextLayout tl;
    tl.createLayout (s, (float) maxTooltipWidth);

    auto bounds = Rectangle<int> (width, height).toFloat();
    bounds = bounds.withSize (jmax (bounds.getWidth(), tl.getWidth()),
                              jmax (bounds.getHeight(), tl.getHeight()));

    const auto bgColour = findColour (TooltipWindow::backgroundColourId);
    jassert (bgColour.isOpaque());
    g.setColour (bgColour);
    g.fillRect (bounds);

    const auto outlineColour = findColour (TooltipWindow::outlineColourId);
    if (! outlineColour.isTransparent())
    {
        g.setColour (outlineColour);
        g.drawRect (bounds, 1.5f);
    }

    tl.draw (g, bounds);
}

//==============================================================================
int MainLookAndFeel::getTabButtonOverlap (int)                                              { return 0; }
int MainLookAndFeel::getTabButtonSpaceAroundImage()                                         { return 0; }
Font MainLookAndFeel::getTabButtonFont (TabBarButton&, float height)                        { return { height * 0.75f }; }
void MainLookAndFeel::drawTabbedButtonBarBackground (TabbedButtonBar&, Graphics&)           { }
void MainLookAndFeel::drawTabAreaBehindFrontButton (TabbedButtonBar&, Graphics&, int, int)  { }

int MainLookAndFeel::getTabButtonBestWidth (TabBarButton& button, int tabDepth)
{
    int width = Font ((float) tabDepth).getStringWidth (button.getButtonText().trim())
                + getTabButtonOverlap (tabDepth) * 2;

    if (auto* extraComponent = button.getExtraComponent())
        width += button.getTabbedButtonBar().isVertical() ? extraComponent->getHeight()
                                                          : extraComponent->getWidth();

    return jlimit (tabDepth * 2, tabDepth * 8, width);
}

Font MainLookAndFeel::getLabelFont (Label& label)
{
    return label.getFont();
}

void MainLookAndFeel::drawTextInRegion (Graphics& g, const Font& font, const String& text, Justification j,
                                                const Rectangle<int>& region, Colour colour, bool isEnabled)
{
    const auto alpha = isEnabled ? 1.0f : 0.5f;

    g.setColour (colour.withMultipliedAlpha (alpha));
    g.setFont (font);
    g.drawFittedText (text, region, j, jmax (1, (int) ((float) region.getHeight() / font.getHeight())), 1.0f);
}

Grid MainLookAndFeel::createDefaultGrid()
{
    Grid grid;
    grid.autoRows = grid.autoColumns = Grid::TrackInfo (1_fr);
    return grid;
}

void MainLookAndFeel::drawLabel (Graphics& g, Label& label)
{
    g.fillAll (label.findColour (Label::backgroundColourId));

    if (! label.isBeingEdited())
    {
        const auto alpha = label.isEnabled() ? 1.0f : 0.5f;

        const auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());
        drawTextInRegion (g, getLabelFont (label), label.getText(), label.getJustificationType(),
                          textArea, label.findColour (Label::textColourId), label.isEnabled());

        g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (Label::outlineColourId));
    }

    g.drawRect (label.getLocalBounds());
}

Rectangle<int> MainLookAndFeel::getTabButtonExtraComponentBounds (const TabBarButton& button, Rectangle<int>& textArea, Component& comp)
{
    Rectangle<int> extraComp;

    auto orientation = button.getTabbedButtonBar().getOrientation();

    if (button.getExtraComponentPlacement() == TabBarButton::beforeText)
    {
        switch (orientation)
        {
            case TabbedButtonBar::TabsAtBottom:
            case TabbedButtonBar::TabsAtTop:     extraComp = textArea.removeFromLeft   (comp.getWidth()); break;
            case TabbedButtonBar::TabsAtLeft:    extraComp = textArea.removeFromBottom (comp.getHeight()); break;
            case TabbedButtonBar::TabsAtRight:   extraComp = textArea.removeFromTop    (comp.getHeight()); break;
            default:                             jassertfalse; break;
        }
    }
    else
    {
        switch (orientation)
        {
            case TabbedButtonBar::TabsAtBottom:
            case TabbedButtonBar::TabsAtTop:     extraComp = textArea.removeFromRight  (comp.getWidth()); break;
            case TabbedButtonBar::TabsAtLeft:    extraComp = textArea.removeFromTop    (comp.getHeight()); break;
            case TabbedButtonBar::TabsAtRight:   extraComp = textArea.removeFromBottom (comp.getHeight()); break;
            default:                             jassertfalse; break;
        }
    }

    return extraComp;
}

void MainLookAndFeel::createTabButtonShape (TabBarButton& button, Path& p, bool, bool)
{
    p.addRectangle (button.getLocalBounds().toFloat());
}

void MainLookAndFeel::fillTabButtonShape (TabBarButton& button, Graphics& g, const Path& path, bool, bool)
{
    auto tabBackground = button.getTabBackgroundColour();
    const bool isFrontTab = button.isFrontTab();

    if (isFrontTab)
    {
        g.setColour (GlobalColours::aquaGreenLike);
        g.fillPath (path);
    }

    g.setColour (isFrontTab ? tabBackground : tabBackground.withMultipliedAlpha (0.9f));
    g.fillPath (path);
}

void MainLookAndFeel::drawTabButtonText (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    auto area = button.getTextArea().toFloat();
    auto length = area.getWidth();
    auto depth  = area.getHeight();

    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);

    auto font = getTabButtonFont (button, depth);
    font.setUnderline (button.hasKeyboardFocus (false));

    AffineTransform t;

    switch (button.getTabbedButtonBar().getOrientation())
    {
        case TabbedButtonBar::TabsAtLeft:   t = t.rotated (MathConstants<float>::pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case TabbedButtonBar::TabsAtRight:  t = t.rotated (MathConstants<float>::pi *  0.5f).translated (area.getRight(), area.getY()); break;

        case TabbedButtonBar::TabsAtTop:
        case TabbedButtonBar::TabsAtBottom:
            t = t.translated (area.getX(), area.getY());
        break;

        default: jassertfalse; break;
    }

    Colour c;

    if (button.isFrontTab() && (button.isColourSpecified (TabbedButtonBar::frontTextColourId) || isColourSpecified (TabbedButtonBar::frontTextColourId)))
        c = findColour (TabbedButtonBar::frontTextColourId);
    else if (button.isColourSpecified (TabbedButtonBar::tabTextColourId) || isColourSpecified (TabbedButtonBar::tabTextColourId))
        c = findColour (TabbedButtonBar::tabTextColourId);
    else
        c = button.getTabBackgroundColour().contrasting();

    const auto alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;

    g.setColour (c.withMultipliedAlpha (alpha));
    g.setFont (font);
    g.addTransform (t);

    g.drawFittedText (button.getButtonText(), 0, 0, (int) length, (int) depth,
                      Justification::centred, jmax (1, ((int) depth) / 12));
}

void MainLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    Path tabShape;
    createTabButtonShape (button, tabShape, isMouseOver, isMouseDown);
    fillTabButtonShape (button, g, tabShape, isMouseOver, isMouseDown);
    drawTabButtonText (button, g, isMouseOver, isMouseDown);
}

Button* MainLookAndFeel::createTabBarExtrasButton()
{
    constexpr auto thickness = 7.0f;
    constexpr auto indent = 22.0f;

    Path p;
    p.addEllipse (-10.0f, -10.0f, 120.0f, 120.0f);

    DrawablePath ellipse;
    ellipse.setPath (p);
    ellipse.setFill (Colour (0x99ffffff));

    p.clear();
    p.addEllipse (0.0f, 0.0f, 100.0f, 100.0f);
    p.addRectangle (indent, 50.0f - thickness, 100.0f - indent * 2.0f, thickness * 2.0f);
    p.addRectangle (50.0f - thickness, indent, thickness * 2.0f, 50.0f - indent - thickness);
    p.addRectangle (50.0f - thickness, 50.0f + thickness, thickness * 2.0f, 50.0f - indent - thickness);
    p.setUsingNonZeroWinding (false);

    DrawablePath dp;
    dp.setPath (p);
    dp.setFill (Colour (0x59000000));

    DrawableComposite normalImage;
    normalImage.addAndMakeVisible (ellipse.createCopy().release());
    normalImage.addAndMakeVisible (dp.createCopy().release());

    dp.setFill (Colour (0xcc000000));

    DrawableComposite overImage;
    overImage.addAndMakeVisible (ellipse.createCopy().release());
    overImage.addAndMakeVisible (dp.createCopy().release());

    auto db = new DrawableButton ("tabs", DrawableButton::ImageFitted);
    db->setImages (&normalImage, &overImage, nullptr);
    return db;
}

void MainLookAndFeel::drawComboBox (Graphics& g, int width, int height, bool isButtonDown,
                                            int, int, int, int, ComboBox& box)
{
    auto cornerSize = box.findParentComponentOfClass<ChoicePropertyComponent>() != nullptr ? 0.0f : DefaultSizes::corner;
    auto boxBounds = Rectangle<int> (width, height).toFloat();

    g.setColour (box.findColour (ComboBox::backgroundColourId));
    g.fillRoundedRectangle (boxBounds, cornerSize);

    g.setColour (box.findColour (ComboBox::outlineColourId));
    g.drawRoundedRectangle (boxBounds.reduced (0.5f, 0.5f), cornerSize, 1.0f);

    const auto arrowZone = Rectangle<int> (width - 30, 0, 20, height).toFloat();
    constexpr auto arrowSize = float_Pi;

    Path path;
    path.addTriangle ({ arrowZone.getX() + arrowSize, arrowZone.getCentreY() - arrowSize },
                      { arrowZone.getCentreX(), arrowZone.getCentreY() + arrowSize},
                      { arrowZone.getRight() - arrowSize, arrowZone.getCentreY() - float_Pi });

    auto pathColour = box.findColour (ComboBox::arrowColourId);
    if (! box.isEnabled())
        pathColour = pathColour.withAlpha (0.2f);
    else if (isButtonDown)
        pathColour = pathColour.withAlpha (0.1f);

    g.setColour (pathColour);
    g.fillPath (path);
}

Font MainLookAndFeel::getTextButtonFont (TextButton&, int buttonHeight)
{
    return { jmin (16.0f, buttonHeight * 0.75f) };
}

void MainLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                                    bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    auto cornerSize = DefaultSizes::corner;
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f, 0.5f);

    auto baseColour = backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                      .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f);

    if (shouldDrawButtonAsDown || shouldDrawButtonAsHighlighted)
        baseColour = baseColour.contrasting (shouldDrawButtonAsDown ? 0.2f : 0.05f);

    if (shouldDrawButtonAsHighlighted)
        baseColour.brighter (1.0f).brighter();

    g.setColour (baseColour);

    auto flatOnLeft   = button.isConnectedOnLeft();
    auto flatOnRight  = button.isConnectedOnRight();
    auto flatOnTop    = button.isConnectedOnTop();
    auto flatOnBottom = button.isConnectedOnBottom();

    if (flatOnLeft || flatOnRight || flatOnTop || flatOnBottom)
    {
        Path path;
        path.addRoundedRectangle (bounds.getX(), bounds.getY(),
                                  bounds.getWidth(), bounds.getHeight(),
                                  cornerSize, cornerSize,
                                  ! (flatOnLeft || flatOnTop),
                                  ! (flatOnRight || flatOnTop),
                                  ! (flatOnLeft || flatOnBottom),
                                  ! (flatOnRight || flatOnBottom));

        g.fillPath (path);
    }
    else
    {
        g.fillRoundedRectangle (bounds, cornerSize);
    }
}

void MainLookAndFeel::drawToggleButton (Graphics& g, ToggleButton& button,
                                                bool shouldDrawButtonAsHighlighted,
                                                bool shouldDrawButtonAsDown)
{
    auto fontSize = jmin (16.0f, button.getHeight() * 0.75f);
    auto tickWidth = fontSize * 1.1f;

    drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                 tickWidth, tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 shouldDrawButtonAsHighlighted,
                 shouldDrawButtonAsDown);

    g.setColour (button.findColour (ToggleButton::textColourId));
    g.setFont (fontSize);

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    g.drawFittedText (button.getButtonText(),
                      button.getLocalBounds().withTrimmedLeft (roundToInt (tickWidth) + 10)
                                             .withTrimmedRight (2),
                      Justification::centredLeft, 10);
}

int MainLookAndFeel::getTextButtonWidthToFitText (TextButton& b, int buttonHeight)
{
    return getTextButtonFont (b, buttonHeight).getStringWidth (b.getButtonText()) + buttonHeight;
}

void MainLookAndFeel::drawDrawableButton (Graphics& g, DrawableButton& button, bool, bool)
{
    bool toggleState = button.getToggleState();

    g.fillAll (button.findColour (toggleState ? DrawableButton::backgroundOnColourId
                                              : DrawableButton::backgroundColourId));

    const int textH = button.getStyle() == DrawableButton::ImageAboveTextLabel
                        ? jmin (16, button.proportionOfHeight (0.25f))
                        : 0;

    if (textH > 0)
    {
        g.setFont ((float) textH);

        g.setColour (button.findColour (toggleState ? DrawableButton::textColourOnId
                                                    : DrawableButton::textColourId)
                            .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.4f));

        g.drawFittedText (button.getButtonText(),
                          2, button.getHeight() - textH - 1,
                          button.getWidth() - 4, textH,
                          Justification::centred, 1);
    }
}

void MainLookAndFeel::changeToggleButtonWidthToFitText (ToggleButton& button)
{
    auto fontSize = jmin (15.0f, button.getHeight() * 0.75f);
    auto tickWidth = fontSize * 1.1f;

    button.setSize (Font (fontSize).getStringWidth (button.getButtonText()) + roundToInt (tickWidth) + 14, button.getHeight());
}

void MainLookAndFeel::drawButtonText (Graphics& g, TextButton& button, bool, bool)
{
    Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    g.setColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                            : TextButton::textColourOffId)
                       .withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));

    const auto cornerSize = DefaultSizes::corner;
    const auto fontHeight = font.getHeight() * 0.75f;

    const int leftIndent  = (int) jmin (fontHeight, 2.0f + cornerSize / (button.isConnectedOnLeft() ? 4.0f : 2.0f));
    const int rightIndent = (int) jmin (fontHeight, 2.0f + cornerSize / (button.isConnectedOnRight() ? 4.0f : 2.0f));
    const int textWidth = button.getWidth() - leftIndent - rightIndent;

    if (textWidth > 0)
        g.drawFittedText (button.getButtonText(),
                          leftIndent, yIndent, textWidth, button.getHeight() - yIndent * 2,
                          Justification::centred, 2);
}

void MainLookAndFeel::drawTickBox (Graphics& g, Component& component,
                                           float x, float y, float w, float h,
                                           const bool ticked,
                                           const bool isEnabled,
                                           const bool shouldDrawButtonAsHighlighted,
                                           const bool shouldDrawButtonAsDown)
{
    ignoreUnused (isEnabled, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

    const auto tickBounds = Rectangle<float> (x, y, w, h);

    g.setColour (component.findColour (ToggleButton::tickDisabledColourId));
    g.drawRoundedRectangle (tickBounds, 4.0f, 1.0f);

    if (ticked)
    {
        g.setColour (component.findColour (ToggleButton::tickColourId));
        auto tick = getTickShape (0.75f);
        g.fillPath (tick, tick.getTransformToScaleToFit (tickBounds.reduced (4.0f, 5.0f), false));
    }
}

void MainLookAndFeel::fillTextEditorBackground (Graphics& g, int width, int height, TextEditor& textEditor)
{
    if (dynamic_cast<AlertWindow*> (textEditor.getParentComponent()) != nullptr)
    {
        g.setColour (textEditor.findColour (TextEditor::backgroundColourId));
        g.fillRect (0, 0, width, height);

        g.setColour (textEditor.findColour (TextEditor::outlineColourId));
        g.drawHorizontalLine (height - 1, 0.0f, static_cast<float> (width));
    }
    else
    {
        g.setColour (textEditor.findColour (TextEditor::backgroundColourId));
        g.fillRoundedRectangle (Rectangle<int> (width, height).toFloat(), DefaultSizes::corner);
    }
}

void MainLookAndFeel::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor)
{
    if (dynamic_cast<AlertWindow*> (textEditor.getParentComponent()) == nullptr)
    {
        if (textEditor.isEnabled())
        {
            if (textEditor.hasKeyboardFocus (true) && ! textEditor.isReadOnly())
                g.setColour (textEditor.findColour (TextEditor::focusedOutlineColourId));
            else
                g.setColour (textEditor.findColour (TextEditor::outlineColourId));

            g.drawRoundedRectangle (Rectangle<int> (width, height).toFloat(), DefaultSizes::corner, 1.0f);
        }
    }
}

float MainLookAndFeel::getCallOutBoxCornerSize (const CallOutBox&)
{
    return DefaultSizes::corner;
}
